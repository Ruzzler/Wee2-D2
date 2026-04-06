// =============================================================================
// Wee2-D2 — Neural Command Center v2.1 (Offline-capable)
// =============================================================================
// Custom web handlers served from Node 2 (Sound Hub):
//   GET  /dash    → Glassmorphic dashboard (HTML from flash PROGMEM)
//   GET  /status  → JSON status of Node 2 wifi + Node 1 heartbeat
//
// Architecture (offline-capable):
//   Phone → GET /dash → Node 2 serves HTML from flash
//   ALL commands → POST (same-origin) → Node 2 entities
//   Node 2 → ESP-NOW radio → Node 1 (animations/lighting/dome)
//   Node 1 → ESP-NOW heartbeat every 5s → Node 2 tracks last-seen
//   Node 1 → UART → Node 3 WLED (lighting presets)
//
// Key: ESP-NOW works at the 802.11 link layer independent of WiFi AP/STA,
// so the full mesh functions even when the droid is offline at a con with
// only Node 2's fallback AP active.
// =============================================================================
#pragma once
#include "esphome.h"
#include "esphome/components/web_server_base/web_server_base.h"
#include "esphome/components/web_server_idf/web_server_idf.h"

using esphome::web_server_idf::AsyncWebHandler;
using esphome::web_server_idf::AsyncWebServerRequest;

static const char DASHBOARD_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1.0,maximum-scale=1.0,user-scalable=no">
<meta name="apple-mobile-web-app-capable" content="yes">
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
<meta name="theme-color" content="#0a0e14">
<title>WEE2-D2 // NEURAL COMMAND</title>
<link rel="preconnect" href="https://fonts.googleapis.com">
<link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;700&family=Roboto+Mono:wght@400;700&display=swap" rel="stylesheet">
<style>
/* ── RESET & VARIABLES ─────────────────────────────────── */
*{margin:0;padding:0;box-sizing:border-box;-webkit-tap-highlight-color:transparent}
:root{
  --bg:#0a0e14;
  --acc:#00d2ff;
  --acc-g:rgba(0,210,255,0.25);
  --red:#ff2d55;
  --red-g:rgba(255,45,85,0.25);
  --teal:#00ffc3;
  --teal-g:rgba(0,255,195,0.15);
  --amber:#ff9f0a;
  --glass:rgba(255,255,255,0.05);
  --border:rgba(255,255,255,0.10);
  --text:#f5f5f0;
  --dim:rgba(255,255,255,0.45);
  --font:'Orbitron',system-ui,sans-serif;
  --mono:'Roboto Mono',monospace;
}

/* ── BODY & AMBIENT BACKGROUND ─────────────────────────── */
body{
  background:var(--bg);color:var(--text);
  font-family:var(--font);
  overflow-x:hidden;min-height:100vh;
  padding-bottom:80px;
}
/* Colored nebulae behind the cards — makes glass visible */
.glow{
  position:fixed;top:-50%;left:-50%;
  width:200%;height:200%;
  background:
    radial-gradient(ellipse at 20% 30%,rgba(0,80,180,0.15) 0%,transparent 50%),
    radial-gradient(ellipse at 80% 70%,rgba(100,0,150,0.10) 0%,transparent 50%),
    radial-gradient(ellipse at 50% 50%,rgba(0,210,255,0.04) 0%,transparent 40%);
  pointer-events:none;z-index:-1;
}

/* ── HEADER ────────────────────────────────────────────── */
header{
  padding:1rem 1.2rem;
  display:flex;justify-content:space-between;align-items:center;
  border-bottom:1px solid var(--border);
  backdrop-filter:blur(12px);-webkit-backdrop-filter:blur(12px);
  background:rgba(10,14,20,0.85);
  position:sticky;top:0;z-index:20;
}
.logo{display:flex;gap:.4rem;font-size:.95rem;font-weight:700;letter-spacing:2px}
.sfx{color:var(--acc)}
.pill{
  padding:.3rem .6rem;border-radius:14px;font-size:.55rem;font-weight:700;
  border:1px solid var(--teal);color:var(--teal);
  background:rgba(0,255,195,0.1);
  transition:all .3s;letter-spacing:0.5px;
  white-space:nowrap;
}
.pill.err{border-color:var(--red);color:var(--red);background:rgba(255,45,85,0.1)}
.pill.cmd{border-color:var(--acc);color:var(--acc);background:rgba(0,210,255,0.15)}

/* ── CONTENT AREA ──────────────────────────────────────── */
.content{
  max-width:600px;margin:0 auto;
  padding:.8rem;
}

/* ── CARDS ─────────────────────────────────────────────── */
.card{
  background:var(--glass);
  backdrop-filter:blur(12px);-webkit-backdrop-filter:blur(12px);
  border:1px solid var(--border);
  border-radius:16px;
  padding:1.2rem;
  margin-bottom:.8rem;
  box-shadow:0 8px 32px rgba(0,0,0,0.36);
  transition:border-color .3s;
}
.card h3{
  font-size:.7rem;margin-bottom:1rem;
  color:var(--acc);letter-spacing:1.5px;
  display:flex;align-items:center;gap:.5rem;
}
.card h3 .dim{
  margin-left:auto;font-size:.5rem;
  color:var(--dim);font-weight:400;
}

/* ── BUTTONS ───────────────────────────────────────────── */
.btn{
  background:rgba(255,255,255,0.06);
  border:1px solid rgba(255,255,255,0.12);
  color:var(--text);
  padding:12px 8px;border-radius:10px;
  font-family:var(--font);font-size:.65rem;
  min-height:48px;cursor:pointer;
  transition:all .15s ease;
  text-align:center;
  letter-spacing:0.5px;
  display:flex;align-items:center;justify-content:center;
  text-transform:uppercase;
  line-height:1.2;
}
.btn:active{transform:scale(0.96);background:rgba(255,255,255,0.10)}
.btn.act{
  background:var(--acc-g);border-color:var(--acc);
  box-shadow:0 0 12px var(--acc-g);color:var(--acc);
}
.btn.red{border-color:rgba(255,45,85,0.5);color:var(--red)}
.btn.red:active{background:var(--red-g)}
.btn.red.act{background:var(--red-g);border-color:var(--red);box-shadow:0 0 12px var(--red-g)}
.btn.teal{border-color:rgba(0,255,195,0.4);color:var(--teal)}
.btn.teal:active{background:var(--teal-g)}
.btn.teal.act{background:var(--teal-g);border-color:var(--teal);box-shadow:0 0 12px var(--teal-g)}
.btn.amber{border-color:rgba(255,159,10,0.4);color:var(--amber)}
.btn.amber:active{background:rgba(255,159,10,0.15)}

/* Pulse animation for button feedback */
@keyframes pulse{
  0%{box-shadow:0 0 0 0 var(--acc-g)}
  70%{box-shadow:0 0 0 8px transparent}
  100%{box-shadow:0 0 0 0 transparent}
}
.btn.ping{animation:pulse .4s ease-out}

/* ── E-STOP ────────────────────────────────────────────── */
.estop-wrap{padding:0 0 .4rem 0}
.estop{
  width:100%;padding:16px;
  background:linear-gradient(135deg,#ff2d55,#ff0040);
  color:#fff;font-weight:700;font-size:.85rem;
  border:none;border-radius:12px;
  box-shadow:0 4px 20px rgba(255,45,85,0.3);
  min-height:56px;cursor:pointer;
  font-family:var(--font);
  letter-spacing:2px;
  transition:all .2s;
  display:flex;align-items:center;justify-content:center;gap:.5rem;
}
.estop:active{
  transform:scale(0.98);
  box-shadow:0 0 40px rgba(255,45,85,0.5);
}

/* ── GRIDS ─────────────────────────────────────────────── */
/* Animation grid: auto-fills so it scales as you add more */
.agrid{
  display:grid;
  grid-template-columns:repeat(auto-fill,minmax(100px,1fr));
  gap:8px;
}
/* Lighting grid: 3 columns on mobile */
.lgrid{
  display:grid;
  grid-template-columns:repeat(3,1fr);
  gap:8px;
}
/* Sound grid: 3 columns */
.sgrid{
  display:grid;
  grid-template-columns:repeat(3,1fr);
  gap:6px;
}

/* ── TABS ──────────────────────────────────────────────── */
.tabs{
  display:flex;gap:6px;margin-bottom:1rem;
}
.tab{
  flex:1;background:transparent;
  border:1px solid var(--border);
  color:var(--dim);
  padding:.55rem;border-radius:8px;
  font-family:var(--font);font-size:.6rem;
  cursor:pointer;transition:all .2s;
  text-align:center;letter-spacing:0.5px;
}
.tab.act{
  background:var(--acc-g);border-color:var(--acc);color:#fff;
}
.tc{display:none}.tc.act{display:block}

/* ── SLIDERS ───────────────────────────────────────────── */
.ctrl-row{margin-bottom:1rem}
.ctrl-row label{
  font-size:.6rem;display:flex;justify-content:space-between;
  margin-bottom:.5rem;color:var(--dim);letter-spacing:1px;
}
.ctrl-row label .val{
  color:var(--acc);font-family:var(--mono);font-weight:700;
}
.sld{
  width:100%;height:6px;
  background:rgba(255,255,255,0.08);
  border-radius:4px;outline:none;
  -webkit-appearance:none;appearance:none;
  cursor:pointer;
}
.sld::-webkit-slider-thumb{
  -webkit-appearance:none;
  width:22px;height:22px;
  background:var(--acc);border-radius:50%;
  cursor:pointer;
  box-shadow:0 0 10px var(--acc-g);
  border:2px solid rgba(0,210,255,0.6);
}
.sld::-moz-range-thumb{
  width:22px;height:22px;
  background:var(--acc);border-radius:50%;
  cursor:pointer;border:2px solid rgba(0,210,255,0.6);
}
.sld::-webkit-slider-runnable-track{border-radius:4px}

/* Volume slider (compact, inside sound card) */
.vol-row{
  display:flex;align-items:center;gap:10px;
  margin-bottom:1rem;
  padding:8px 12px;
  background:rgba(0,0,0,0.2);border-radius:10px;
  border:1px solid rgba(255,255,255,0.06);
}
.vol-row label{font-size:.55rem;color:var(--dim);letter-spacing:1px;min-width:28px}
.vol-row .sld{flex:1;height:4px}
.vol-row .val{
  font-size:.7rem;color:var(--acc);
  font-family:var(--mono);font-weight:700;
  min-width:20px;text-align:right;
}

/* Stop audio button */
.stop-audio{
  width:100%;margin-top:10px;
  border-color:rgba(255,45,85,0.4);
  color:var(--red);font-weight:700;
  font-size:.7rem;letter-spacing:1px;
}

/* ── CONFIG SECTION ────────────────────────────────────── */
.cfg-row{
  display:flex;gap:8px;align-items:center;margin-top:.8rem;
}
.cfg-row label{
  font-size:.55rem;color:var(--dim);
  min-width:55px;letter-spacing:0.5px;
}
.cfg-inp{
  background:rgba(0,0,0,0.3);
  border:1px solid var(--border);
  color:var(--acc);
  padding:8px 10px;border-radius:8px;
  font-family:var(--mono);font-size:.65rem;
  width:100%;
}
.cfg-inp:focus{outline:none;border-color:var(--acc)}

/* ── FOOTER ────────────────────────────────────────────── */
footer{
  padding:1rem 1.2rem;
  display:flex;justify-content:space-between;
  font-size:.55rem;color:rgba(255,255,255,0.25);
  border-top:1px solid var(--border);
  font-family:var(--mono);letter-spacing:0.5px;
  max-width:600px;margin:0 auto;
}

/* ── TOAST ─────────────────────────────────────────────── */
.toast{
  position:fixed;bottom:20px;left:50%;
  transform:translateX(-50%) translateY(20px);
  background:rgba(20,20,30,0.92);
  backdrop-filter:blur(12px);-webkit-backdrop-filter:blur(12px);
  color:#fff;padding:10px 24px;
  border-radius:12px;font-size:.7rem;
  font-family:var(--font);
  opacity:0;transition:all .35s cubic-bezier(.4,0,.2,1);
  pointer-events:none;z-index:50;
  border:1px solid var(--border);
  letter-spacing:0.5px;
  max-width:90vw;
}
.toast.show{opacity:1;transform:translateX(-50%) translateY(0)}
.toast.ok{border-left:3px solid var(--teal)}
.toast.err{border-left:3px solid var(--red)}

/* ── RESPONSIVE ────────────────────────────────────────── */
@media(max-width:400px){
  .sgrid{grid-template-columns:repeat(2,1fr)}
  .lgrid{grid-template-columns:repeat(3,1fr)}
  header{padding:.7rem .8rem}
  .logo{font-size:.8rem}
  .content{padding:.6rem}
}
@media(min-width:500px){
  .lgrid{grid-template-columns:repeat(4,1fr)}
}
@media(min-width:700px){
  .lgrid{grid-template-columns:repeat(5,1fr)}
  .sgrid{grid-template-columns:repeat(4,1fr)}
}

/* ── SECTION DIVIDER ───────────────────────────────────── */
.sep{
  height:1px;
  background:linear-gradient(90deg,transparent,var(--border),transparent);
  margin:.4rem 0;
}

/* ── STATUS CARD (Node health panel) ──────────────────── */
.status{
  display:grid;grid-template-columns:1fr 1fr;gap:8px;
  font-family:var(--mono);font-size:.6rem;
}
.nbox{
  background:rgba(0,0,0,0.25);
  border:1px solid var(--border);
  border-radius:10px;
  padding:.6rem .7rem;
  position:relative;
  overflow:hidden;
}
.nbox.on{border-color:rgba(0,255,195,0.4);background:rgba(0,255,195,0.05)}
.nbox.off{border-color:rgba(255,45,85,0.4);background:rgba(255,45,85,0.05)}
.nbox .nhead{
  display:flex;justify-content:space-between;align-items:center;
  margin-bottom:.35rem;
}
.nbox .nname{
  font-weight:700;letter-spacing:1px;font-size:.6rem;
  color:var(--text);
}
.dot{
  width:8px;height:8px;border-radius:50%;
  background:var(--dim);display:inline-block;
  box-shadow:0 0 0 0 transparent;
}
.dot.on{background:var(--teal);box-shadow:0 0 8px var(--teal)}
.dot.off{background:var(--red);box-shadow:0 0 8px var(--red)}
.dot.pulse{animation:pulse 1.8s ease-in-out infinite}
@keyframes pulse{
  0%,100%{opacity:1;transform:scale(1)}
  50%{opacity:.55;transform:scale(.85)}
}
.nrow{
  display:flex;justify-content:space-between;
  color:var(--dim);font-size:.55rem;line-height:1.5;
  letter-spacing:0.3px;
}
.nrow b{color:var(--acc);font-weight:400}
.nrow .off-val{color:var(--red)}
.nrow .ok-val{color:var(--teal)}
.ap-badge{
  display:inline-block;font-size:.5rem;font-weight:700;
  padding:1px 5px;border-radius:3px;letter-spacing:0.5px;
  background:var(--amber);color:#000;margin-left:4px;
}
</style>
</head>
<body>
<div class="glow"></div>

<!-- ═══════════════════════════════════════════════════════
     HEADER — Sticky, always visible
     ═══════════════════════════════════════════════════════ -->
<header>
  <div class="logo"><span>WEE2-D2</span><span class="sfx">NEURAL COMMAND</span></div>
  <div class="pill" id="st">CONNECTING</div>
</header>

<div class="content">

  <!-- ═════════════════════════════════════════════════════
       EMERGENCY STOP — Always first, always visible
       ═════════════════════════════════════════════════════ -->
  <div class="estop-wrap">
    <button class="estop" onclick="eStop()">&#9888; EMERGENCY STOP</button>
  </div>

  <!-- ═════════════════════════════════════════════════════
       MESH STATUS — Polled every 3s from /status
       ═════════════════════════════════════════════════════ -->
  <section class="card">
    <h3>&#128225; MESH STATUS</h3>
    <div class="status">
      <div class="nbox" id="n2box">
        <div class="nhead">
          <span class="nname">NODE 2 // SOUND<span id="n2ap"></span></span>
          <span class="dot pulse" id="n2dot"></span>
        </div>
        <div class="nrow"><span>IP</span><b id="n2ip">--</b></div>
        <div class="nrow"><span>SSID</span><b id="n2ssid">--</b></div>
        <div class="nrow"><span>RSSI</span><b id="n2rssi">--</b></div>
        <div class="nrow"><span>UP</span><b id="n2up">--</b></div>
      </div>
      <div class="nbox" id="n1box">
        <div class="nhead">
          <span class="nname">NODE 1 // BRAIN</span>
          <span class="dot pulse" id="n1dot"></span>
        </div>
        <div class="nrow"><span>LINK</span><b id="n1link">--</b></div>
        <div class="nrow"><span>LAST PING</span><b id="n1age">--</b></div>
        <div class="nrow"><span>PINGS</span><b id="n1pings">--</b></div>
        <div class="nrow"><span>VIA</span><b>ESP-NOW</b></div>
      </div>
    </div>
  </section>

  <!-- ═════════════════════════════════════════════════════
       ANIMATIONS — Auto-expanding grid
       Add more buttons here as new animations are created.
       The grid auto-flows to fit any number of buttons.
       ═════════════════════════════════════════════════════ -->
  <section class="card">
    <h3>&#9889; ANIMATIONS <span class="dim" id="acnt">3 LOADED</span></h3>
    <div class="agrid" id="agrid">
      <button class="btn act" data-anim="reset_to_idle" onclick="anim(this)">IDLE</button>
      <button class="btn amber" data-anim="angry_tantrum" onclick="anim(this)">ANGRY</button>
      <button class="btn teal" data-anim="dance_party" onclick="anim(this)">DANCE</button>
      <button class="btn" data-anim="cantina" onclick="anim(this)">CANTINA</button>
      <!-- ═══════════════════════════════════════════════
           ADD MORE ANIMATION BUTTONS BELOW
           Pattern: <button class="btn" data-anim="slug_name" onclick="anim(this)">LABEL</button>
           The data-anim value must match the Node 1 button slug:
             name: "Animation: My New Anim" → slug: my_new_anim
           ═══════════════════════════════════════════════ -->
    </div>
  </section>

  <!-- ═════════════════════════════════════════════════════
       LIGHTING PRESETS — Categorized, all 15 + All Off
       Calls Node 1 select via cross-node REST
       ═════════════════════════════════════════════════════ -->
  <section class="card">
    <h3>&#128161; LIGHTING PRESETS</h3>

    <!-- Tabbed categories -->
    <div class="tabs">
      <button class="tab act" onclick="oTab(event,'l-all')">ALL</button>
      <button class="tab" onclick="oTab(event,'l-mood')">MOODS</button>
      <button class="tab" onclick="oTab(event,'l-zone')">ZONES</button>
      <button class="tab" onclick="oTab(event,'l-scene')">SCENES</button>
    </div>

    <!-- ALL — flat grid, every preset -->
    <div id="l-all" class="tc act">
      <div class="lgrid">
        <button class="btn lbtn act" onclick="led(this,'1977 Idle')">1977 Idle</button>
        <button class="btn lbtn" onclick="led(this,'Neural Processing')">Neural Proc</button>
        <button class="btn lbtn" onclick="led(this,'Full Alert')">Full Alert</button>
        <button class="btn lbtn" onclick="led(this,'Front Logic Only')">Front Logic</button>
        <button class="btn lbtn" onclick="led(this,'Rear Logic Only')">Rear Logic</button>
        <button class="btn lbtn" onclick="led(this,'PSI Scan')">PSI Scan</button>
        <button class="btn lbtn" onclick="led(this,'Data Transfer')">Data Xfer</button>
        <button class="btn lbtn" onclick="led(this,'Leia Message')">Leia Msg</button>
        <button class="btn lbtn" onclick="led(this,'Disco Mode')">Disco</button>
        <button class="btn lbtn" onclick="led(this,'Stealth')">Stealth</button>
        <button class="btn lbtn" onclick="led(this,'Startup Sequence')">Boot Seq</button>
        <button class="btn lbtn" onclick="led(this,'Malfunction')">Malfunction</button>
        <button class="btn lbtn" onclick="led(this,'Celebration')">Celebrate</button>
        <button class="btn lbtn" onclick="led(this,'Imperial March')">Imp. March</button>
        <button class="btn lbtn" onclick="led(this,'All Off')" style="color:var(--dim)">All Off</button>
      </div>
    </div>

    <!-- MOODS — emotional/state presets -->
    <div id="l-mood" class="tc">
      <div class="lgrid">
        <button class="btn lbtn" onclick="led(this,'1977 Idle')">1977 Idle</button>
        <button class="btn lbtn" onclick="led(this,'Neural Processing')">Neural Proc</button>
        <button class="btn lbtn" onclick="led(this,'Full Alert')">Full Alert</button>
        <button class="btn lbtn" onclick="led(this,'Stealth')">Stealth</button>
        <button class="btn lbtn" onclick="led(this,'Malfunction')">Malfunction</button>
        <button class="btn lbtn" onclick="led(this,'All Off')" style="color:var(--dim)">All Off</button>
      </div>
    </div>

    <!-- ZONES — individual panel control -->
    <div id="l-zone" class="tc">
      <div class="lgrid">
        <button class="btn lbtn" onclick="led(this,'Front Logic Only')">Front Logic</button>
        <button class="btn lbtn" onclick="led(this,'Rear Logic Only')">Rear Logic</button>
        <button class="btn lbtn" onclick="led(this,'PSI Scan')">PSI Scan</button>
        <button class="btn lbtn" onclick="led(this,'All Off')" style="color:var(--dim)">All Off</button>
      </div>
    </div>

    <!-- SCENES — performance/event presets -->
    <div id="l-scene" class="tc">
      <div class="lgrid">
        <button class="btn lbtn" onclick="led(this,'Disco Mode')">Disco</button>
        <button class="btn lbtn" onclick="led(this,'Celebration')">Celebrate</button>
        <button class="btn lbtn" onclick="led(this,'Imperial March')">Imp. March</button>
        <button class="btn lbtn" onclick="led(this,'Leia Message')">Leia Msg</button>
        <button class="btn lbtn" onclick="led(this,'Data Transfer')">Data Xfer</button>
        <button class="btn lbtn" onclick="led(this,'Startup Sequence')">Boot Seq</button>
      </div>
    </div>
  </section>

  <!-- ═════════════════════════════════════════════════════
       SOUND HUB — Tabbed soundboard with volume control
       All calls are local (Node 2 same-origin)
       ═════════════════════════════════════════════════════ -->
  <section class="card">
    <h3>&#9835; SOUND HUB</h3>

    <!-- Volume slider (compact, always visible) -->
    <div class="vol-row">
      <label>VOL</label>
      <input type="range" min="1" max="26" value="26" step="1" class="sld" id="vol"
             oninput="document.getElementById('vval').textContent=this.value"
             onchange="setVol(this.value)">
      <span class="val" id="vval">26</span>
    </div>

    <!-- Sound category tabs -->
    <div class="tabs">
      <button class="tab act" onclick="oTab(event,'t-sfx')">SFX</button>
      <button class="tab" onclick="oTab(event,'t-mus')">MUSIC</button>
      <button class="tab" onclick="oTab(event,'t-spc')">SPECIAL</button>
    </div>

    <!-- SFX Tab: 12 random category buttons -->
    <div id="t-sfx" class="tc act">
      <div class="sgrid">
        <button class="btn" onclick="snd('sfx_random_happy')">Happy</button>
        <button class="btn" onclick="snd('sfx_random_sad')">Sad</button>
        <button class="btn" onclick="snd('sfx_random_alarm')">Alarm</button>
        <button class="btn" onclick="snd('sfx_random_scream')">Scream</button>
        <button class="btn" onclick="snd('sfx_random_whistle')">Whistle</button>
        <button class="btn" onclick="snd('sfx_random_hum')">Hum</button>
        <button class="btn" onclick="snd('sfx_random_misc')">Misc</button>
        <button class="btn" onclick="snd('sfx_random_razz')">Razz</button>
        <button class="btn" onclick="snd('sfx_random_proc')">Process</button>
        <button class="btn" onclick="snd('sfx_random_ooh')">Ooh</button>
        <button class="btn" onclick="snd('sfx_random_sent')">Sentence</button>
        <button class="btn" onclick="snd('sfx_random_quotes')">Quotes</button>
      </div>
    </div>

    <!-- Music Tab: ALL 24 tracks organized -->
    <div id="t-mus" class="tc">
      <div style="font-size:.5rem;color:var(--dim);margin-bottom:6px;letter-spacing:1px">STAR WARS</div>
      <div class="sgrid" style="margin-bottom:10px">
        <button class="btn" onclick="snd('sfx_cantina_short')">Cantina</button>
        <button class="btn" onclick="snd('sfx_cantina_full')">Cantina Full</button>
        <button class="btn" onclick="snd('sfx_sw_theme_1')">SW Theme 1</button>
        <button class="btn" onclick="snd('sfx_sw_theme_2')">SW Theme 2</button>
        <button class="btn" onclick="snd('sfx_sw_theme_3')">SW Theme 3</button>
        <button class="btn" onclick="snd('sfx_celebration')">Celebration</button>
        <button class="btn" onclick="snd('sfx_leia_message')">Leia Msg</button>
        <button class="btn" onclick="snd('sfx_luke_to_jabba')">Luke Jabba</button>
        <button class="btn" onclick="snd('sfx_r2_in_love')">R2 In Love</button>
        <button class="btn" onclick="snd('sfx_sw_disco')">SW Disco</button>
      </div>
      <div style="font-size:.5rem;color:var(--dim);margin-bottom:6px;letter-spacing:1px">PARTY &amp; POP</div>
      <div class="sgrid" style="margin-bottom:10px">
        <button class="btn" onclick="snd('sfx_uptown_funk')">Uptown Funk</button>
        <button class="btn" onclick="snd('sfx_harlem_shake')">Harlem Shake</button>
        <button class="btn" onclick="snd('sfx_ghostbusters')">Ghostbusters</button>
        <button class="btn" onclick="snd('sfx_macho_man')">Macho Man</button>
        <button class="btn" onclick="snd('sfx_stayin_alive')">Stayin Alive</button>
        <button class="btn" onclick="snd('sfx_gangnam_style')">Gangnam</button>
        <button class="btn" onclick="snd('sfx_mhana_mhana')">Mhana Mhana</button>
      </div>
      <div style="font-size:.5rem;color:var(--dim);margin-bottom:6px;letter-spacing:1px">TV &amp; OTHER</div>
      <div class="sgrid">
        <button class="btn" onclick="snd('sfx_addams_family')">Addams Family</button>
        <button class="btn" onclick="snd('sfx_buffy_theme')">Buffy</button>
        <button class="btn" onclick="snd('sfx_firefly_theme')">Firefly</button>
        <button class="btn" onclick="snd('sfx_canton')">Canton</button>
        <button class="btn" onclick="snd('sfx_peanut')">Peanut</button>
        <button class="btn" onclick="snd('sfx_birthday')">Birthday</button>
      </div>
    </div>

    <!-- Special Tab: ALL 29 effects organized -->
    <div id="t-spc" class="tc">
      <div style="font-size:.5rem;color:var(--dim);margin-bottom:6px;letter-spacing:1px">DROID SOUNDS</div>
      <div class="sgrid" style="margin-bottom:10px">
        <button class="btn" onclick="snd('sfx_startup')">Startup</button>
        <button class="btn" onclick="snd('sfx_short_circuit')">Short Circuit</button>
        <button class="btn" onclick="snd('sfx_motivator_fail')">Motivator</button>
        <button class="btn" onclick="snd('sfx_failure')">Failure</button>
        <button class="btn" onclick="snd('sfx_annoyed')">Annoyed</button>
        <button class="btn" onclick="snd('sfx_chortle')">Chortle</button>
        <button class="btn" onclick="snd('sfx_groan')">Groan</button>
        <button class="btn" onclick="snd('sfx_overhere')">Over Here!</button>
        <button class="btn" onclick="snd('sfx_question')">Question</button>
        <button class="btn" onclick="snd('sfx_wowie')">Wowie</button>
        <button class="btn" onclick="snd('sfx_wolf_whistle')">Wolf Whistle</button>
      </div>
      <div style="font-size:.5rem;color:var(--dim);margin-bottom:6px;letter-spacing:1px">EFFECTS &amp; ROBOTS</div>
      <div class="sgrid" style="margin-bottom:10px">
        <button class="btn" onclick="snd('sfx_cylon')">Cylon</button>
        <button class="btn" onclick="snd('sfx_doodoo')">DooDoo</button>
        <button class="btn" onclick="snd('sfx_nokia')">Nokia</button>
        <button class="btn" onclick="snd('sfx_patrol')">Patrol</button>
        <button class="btn" onclick="snd('sfx_j5_laser')">J5 Laser</button>
      </div>
      <div style="font-size:.5rem;color:var(--dim);margin-bottom:6px;letter-spacing:1px">JINGLES</div>
      <div class="sgrid" style="margin-bottom:10px">
        <button class="btn" onclick="snd('sfx_jingle_1')">Jingle 1</button>
        <button class="btn" onclick="snd('sfx_jingle_2')">Jingle 2</button>
        <button class="btn" onclick="snd('sfx_jingle_3')">Jingle 3</button>
      </div>
      <div style="font-size:.5rem;color:var(--dim);margin-bottom:6px;letter-spacing:1px">JOHNNY 5</div>
      <div class="sgrid" style="margin-bottom:10px">
        <button class="btn" onclick="snd('sfx_johnny5_1')">Johnny5 1</button>
        <button class="btn" onclick="snd('sfx_johnny5_2')">Johnny5 2</button>
        <button class="btn" onclick="snd('sfx_johnny5_3')">Johnny5 3</button>
        <button class="btn" onclick="snd('sfx_johnny5_4')">Johnny5 4</button>
        <button class="btn" onclick="snd('sfx_johnny5_5')">Johnny5 5</button>
        <button class="btn" onclick="snd('sfx_johnny5_6')">Johnny5 6</button>
      </div>
      <div style="font-size:.5rem;color:var(--dim);margin-bottom:6px;letter-spacing:1px">ROBOT CITY</div>
      <div class="sgrid">
        <button class="btn" onclick="snd('sfx_robocity_1')">RoboCity 1</button>
        <button class="btn" onclick="snd('sfx_robocity_2')">RoboCity 2</button>
        <button class="btn" onclick="snd('sfx_robocity_3')">RoboCity 3</button>
        <button class="btn" onclick="snd('sfx_robocity_4')">RoboCity 4</button>
      </div>
    </div>

    <!-- Stop Audio — always visible below tabs -->
    <button class="btn stop-audio" onclick="snd('sfx_stop')">&#9724; STOP AUDIO</button>
  </section>

  <!-- ═════════════════════════════════════════════════════
       SYSTEMS — Dome speed (relayed via ESP-NOW to Node 1)
       ═════════════════════════════════════════════════════ -->
  <section class="card">
    <h3>&#9881; SYSTEMS</h3>
    <div class="ctrl-row">
      <label>DOME SPEED <span class="val" id="dval">0.60</span></label>
      <input type="range" min="10" max="100" value="60" step="5" class="sld" id="dspd"
             oninput="document.getElementById('dval').textContent=(this.value/100).toFixed(2)"
             onchange="setDome(this.value)">
    </div>
    <div style="font-size:.5rem;color:rgba(255,255,255,0.2);margin-top:.6rem;letter-spacing:0.3px">
      All cross-node commands relay via ESP-NOW radio — works offline.
    </div>
  </section>

</div><!-- /.content -->

<footer>
  <span>v2.6.0-Dashboard</span>
  <span id="up">UPTIME 00:00:00</span>
</footer>

<div class="toast" id="toast"></div>

<script>
// ═══════════════════════════════════════════════════════════
// NEURAL COMMAND CENTER — Control Logic
// ═══════════════════════════════════════════════════════════

var es=null;      // EventSource connection
var upSec=0;      // Uptime counter
var activeLed=''; // Currently active LED preset name
var n1alive=false;// Tracks Node 1 heartbeat state

// Animation name → relay button slug on Node 2
var ANIM_SLUG={
  'reset_to_idle':'relay_animation_idle',
  'angry_tantrum':'relay_animation_angry',
  'dance_party':'relay_animation_dance',
  'cantina':'relay_animation_cantina'
};

// ── INIT ──────────────────────────────────────────────────
function init(){
  initES();
  initUp();
  pollStatus();             // First poll immediately
  setInterval(pollStatus,3000);
  pill('','MESH LINKED');
  // Update animation count badge
  var cnt=document.getElementById('agrid').children.length;
  document.getElementById('acnt').textContent=cnt+' LOADED';
}

// ── STATUS PILL ───────────────────────────────────────────
function pill(cls,txt){
  var p=document.getElementById('st');
  p.className='pill'+(cls?' '+cls:'');
  p.textContent=txt;
}
function flash(){
  pill('cmd','COMMAND SENT');
  setTimeout(function(){pill('','MESH LINKED')},800);
}

// ── TOAST ─────────────────────────────────────────────────
function toast(msg,cls){
  var t=document.getElementById('toast');
  t.textContent=msg;
  t.className='toast show'+(cls?' '+cls:'');
  setTimeout(function(){t.className='toast'},2000);
}

// ── ANIMATIONS (Local → Node 2 → ESP-NOW → Node 1) ───────
function anim(btn){
  var name=btn.getAttribute('data-anim');
  var slug=ANIM_SLUG[name];
  if(!slug){toast('Unknown animation: '+name,'err');return;}
  fetch('/button/'+slug+'/press',{method:'POST'}).then(function(r){
    if(!r.ok) toast('Anim: HTTP '+r.status,'err');
  }).catch(function(){toast('Anim: network error','err')});
  // Visual feedback: brief pulse
  var all=document.querySelectorAll('.agrid .btn');
  all.forEach(function(b){b.classList.remove('act')});
  btn.classList.add('act');
  btn.classList.add('ping');
  setTimeout(function(){btn.classList.remove('ping')},400);
  flash();
  toast('Anim: '+name.replace(/_/g,' ').toUpperCase(),'ok');
}

// ── E-STOP (Single call — Node 2 handles local + relays to Node 1) ──
function eStop(){
  fetch('/button/emergency_stop_all/press',{method:'POST'}).catch(function(){
    toast('E-Stop failed','err');
  });
  pill('err','E-STOP ACTIVE');
  toast('EMERGENCY STOP TRIGGERED','err');
  // Clear animation highlights
  var ab=document.querySelectorAll('.agrid .btn');
  ab.forEach(function(b){b.classList.remove('act')});
  setTimeout(function(){pill('','MESH LINKED')},3000);
}

// ── LIGHTING PRESETS (Local → Node 2 relay select → ESP-NOW → Node 1) ──
function led(btn,name){
  fetch('/select/relay_lighting_preset/set?option='+encodeURIComponent(name),
    {method:'POST'}).catch(function(){toast('LED: network error','err')});
  // Track active preset
  var all=document.querySelectorAll('.lbtn');
  all.forEach(function(b){b.classList.remove('act')});
  btn.classList.add('act');
  activeLed=name;
  flash();
  toast('LED: '+name,'ok');
}

// ── SOUND TRIGGERS (Local → Node 2 direct) ───────────────
function snd(id){
  fetch('/button/'+id+'/press',{method:'POST'}).then(function(r){
    if(r.ok) toast('Sound: '+id.replace('sfx_','').replace(/_/g,' '),'ok');
    else toast('Sound: HTTP '+r.status,'err');
  }).catch(function(){toast('Sound: network error','err')});
  flash();
}

// ── VOLUME (Local → Node 2) ──────────────────────────────
function setVol(v){
  document.getElementById('vval').textContent=v;
  fetch('/number/audio_volume/set?value='+v,{method:'POST'}).catch(function(){
    toast('Volume failed','err');
  });
}

// ── DOME SPEED (Local → Node 2 relay number → ESP-NOW → Node 1) ──
// Slider value is 10-100; we display as 0.10-1.00 but send the integer.
function setDome(v){
  document.getElementById('dval').textContent=(v/100).toFixed(2);
  fetch('/number/relay_dome_speed/set?value='+v,{method:'POST'}).catch(function(){
    toast('Dome: network error','err');
  });
  toast('Dome: '+(v/100).toFixed(2),'ok');
}

// ── STATUS POLL (GET /status every 3s) ───────────────────
function pollStatus(){
  fetch('/status',{cache:'no-store'}).then(function(r){
    if(!r.ok) throw new Error('HTTP '+r.status);
    return r.json();
  }).then(function(d){
    // ── Node 2 (self) ───────────────────────────────────
    var n2=d.node2||{};
    var n2box=document.getElementById('n2box');
    var n2dot=document.getElementById('n2dot');
    n2box.classList.remove('off');
    n2box.classList.add('on');
    n2dot.classList.remove('off','pulse');
    n2dot.classList.add('on');
    document.getElementById('n2ip').textContent=n2.ip||'--';
    document.getElementById('n2ssid').textContent=n2.ssid||'--';
    document.getElementById('n2rssi').textContent=
      (n2.rssi!=null?n2.rssi+' dBm':'--');
    document.getElementById('n2up').textContent=fmtUp(n2.uptime_s||0);
    document.getElementById('n2ap').innerHTML=
      n2.ap_mode?'<span class="ap-badge">AP</span>':'';

    // ── Node 1 (remote via ESP-NOW heartbeat) ───────────
    var n1=d.node1||{};
    var n1box=document.getElementById('n1box');
    var n1dot=document.getElementById('n1dot');
    n1alive=!!n1.online;
    if(n1.online){
      n1box.classList.remove('off');
      n1box.classList.add('on');
      n1dot.classList.remove('off','pulse');
      n1dot.classList.add('on');
      document.getElementById('n1link').innerHTML=
        '<span class="ok-val">ONLINE</span>';
    }else{
      n1box.classList.remove('on');
      n1box.classList.add('off');
      n1dot.classList.remove('on');
      n1dot.classList.add('off','pulse');
      document.getElementById('n1link').innerHTML=
        '<span class="off-val">OFFLINE</span>';
    }
    document.getElementById('n1age').textContent=
      (n1.age_s!=null && n1.age_s<9999?n1.age_s+'s ago':'--');
    document.getElementById('n1pings').textContent=
      (n1.heartbeats!=null?n1.heartbeats:'--');
  }).catch(function(){
    // Mark both nodes as unreachable if /status itself fails
    var n2dot=document.getElementById('n2dot');
    n2dot.classList.remove('on');
    n2dot.classList.add('off');
    document.getElementById('n1link').innerHTML=
      '<span class="off-val">NO DATA</span>';
  });
}

function fmtUp(s){
  s=parseInt(s)||0;
  var h=Math.floor(s/3600),m=Math.floor((s%3600)/60),ss=s%60;
  if(h>0) return h+'h '+m+'m';
  if(m>0) return m+'m '+ss+'s';
  return ss+'s';
}

// ── TABS ──────────────────────────────────────────────────
function oTab(e,id){
  var tcs=document.getElementsByClassName('tc');
  for(var i=0;i<tcs.length;i++) tcs[i].classList.remove('act');
  var tabs=document.getElementsByClassName('tab');
  for(var i=0;i<tabs.length;i++) tabs[i].classList.remove('act');
  document.getElementById(id).classList.add('act');
  e.currentTarget.classList.add('act');
}

// ── EVENTSOURCE (State feedback from Node 2) ─────────────
function initES(){
  if(es) es.close();
  es=new EventSource('/events');
  es.addEventListener('state',function(e){
    try{
      var d=JSON.parse(e.data);
      var sid=d.id||'';
      var v=d.value;
      // Sync volume slider if changed externally
      if(sid.indexOf('audio_volume')>-1 && v!=null){
        document.getElementById('vol').value=Math.round(v);
        document.getElementById('vval').textContent=Math.round(v);
      }
    }catch(ex){}
  });
  es.onerror=function(){
    pill('err','LINK LOST');
    setTimeout(initES,5000);
  };
  es.onopen=function(){
    pill('','MESH LINKED');
  };
}

// ── UPTIME ────────────────────────────────────────────────
function initUp(){
  setInterval(function(){
    upSec++;
    var h=Math.floor(upSec/3600).toString().padStart(2,'0');
    var m=Math.floor((upSec%3600)/60).toString().padStart(2,'0');
    var s=(upSec%60).toString().padStart(2,'0');
    document.getElementById('up').textContent='UPTIME '+h+':'+m+':'+s;
  },1000);
}

// ── BOOT ──────────────────────────────────────────────────
document.addEventListener('DOMContentLoaded',init);
</script>
</body>
</html>
)rawliteral";

// =============================================================================
// Handler class — Serves the dashboard at /dash
// Uses ESPHome's internal web_server_idf types (const canHandle signature).
// =============================================================================
class DashboardHandler : public AsyncWebHandler {
 public:
  bool canHandle(AsyncWebServerRequest *request) const override {
    return request->url() == "/dash";
  }
  void handleRequest(AsyncWebServerRequest *request) override {
    request->send(200, "text/html", DASHBOARD_HTML);
  }
};

// =============================================================================
// Status handler — GET /status
// Returns JSON with:
//   - Node 2 self info: IP, SSID, RSSI, uptime, firmware
//   - Node 1 remote info: online state (based on ESP-NOW heartbeat),
//     seconds since last ping, total heartbeat count
// Dashboard polls this every 3 seconds to drive the status card.
// =============================================================================
class StatusHandler : public AsyncWebHandler {
 public:
  bool canHandle(AsyncWebServerRequest *request) const override {
    return request->url() == "/status";
  }
  void handleRequest(AsyncWebServerRequest *request) override {
    char buf[512];
    uint32_t now = millis();
    uint32_t last_seen = id(node1_last_seen_ms);
    uint32_t age_ms = (last_seen > 0) ? (now - last_seen) : 0xFFFFFFFF;
    bool node1_online = (last_seen > 0) && (age_ms < 15000);
    uint32_t age_s = (last_seen > 0) ? (age_ms / 1000) : 9999;

    // Pull live WiFi state (falls back to empty strings if unavailable)
    std::string ip   = id(wifi_ip_sensor).has_state()   ? id(wifi_ip_sensor).state   : std::string("");
    std::string ssid = id(wifi_ssid_sensor).has_state() ? id(wifi_ssid_sensor).state : std::string("");
    float rssi   = id(wifi_rssi_sensor).has_state()     ? id(wifi_rssi_sensor).state : 0.0f;
    float uptime = id(up_time_sensor).has_state()       ? id(up_time_sensor).state   : 0.0f;

    // Detect AP-fallback mode: if there's no STA IP, assume we're the hotspot
    bool ap_mode = (ip.empty() || ip == "0.0.0.0");

    snprintf(buf, sizeof(buf),
      "{\"node2\":{"
        "\"ip\":\"%s\","
        "\"ssid\":\"%s\","
        "\"rssi\":%d,"
        "\"uptime_s\":%u,"
        "\"ap_mode\":%s,"
        "\"fw\":\"2.6.0-Dashboard\""
      "},"
      "\"node1\":{"
        "\"online\":%s,"
        "\"age_s\":%u,"
        "\"heartbeats\":%u,"
        "\"fw\":\"2.6.0-Dashboard\""
      "}}",
      ip.c_str(),
      ssid.c_str(),
      (int)rssi,
      (unsigned)uptime,
      ap_mode ? "true" : "false",
      node1_online ? "true" : "false",
      (unsigned)age_s,
      (unsigned)id(node1_heartbeat_count));

    auto *response = request->beginResponse(200, "application/json", buf);
    response->addHeader("Cache-Control", "no-store");
    request->send(response);
  }
};
