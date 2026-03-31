# Custom GitHub Actions Runner with ESPHome
FROM myoung34/github-runner:latest

# Install Python and dependencies required for ESPHome
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    python3-venv \
    && rm -rf /var/lib/apt/lists/*

# Install ESPHome
RUN pip3 install --no-cache-dir esphome

# Ensure the runner has access to local network discovery (mDNS)
RUN apt-get update && apt-get install -y \
    avahi-daemon \
    libavahi-compat-libdnssd-dev \
    && rm -rf /var/lib/apt/lists/*

LABEL maintainer="Wee2-D2 Droid Engineering"
LABEL version="v2.0-Hybrid"
