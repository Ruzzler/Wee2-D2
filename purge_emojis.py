import os
import re

# Regex for all emojis and some extra symbols found in the grep
# This covers basic emojis and extended ones
emoji_pattern = re.compile(
    "["
    "\U0001f300-\U0001fad6"  # Miscellaneous Symbols and Pictographs to Symbols and Pictographs Extended-A
    "\U0001f600-\U0001f64f"  # Emoticons
    "\U0001f680-\U0001f6ff"  # Transport and Map Symbols
    "\U0001f900-\U0001f9ff"  # Supplemental Symbols and Pictographs
    "\u2600-\u27bf"          # Miscellaneous Symbols and Dingbats
    "\u2300-\u23ff"          # Miscellaneous Technical
    "\U0001f1e6-\U0001f1ff"  # Flags
    "\U0001f004-\U0001f0cf"  # Mahjong/Domino/Playing Cards
    "\U0001f300-\U0001f5ff"  # More symbols
    "👉🚫🤫🏗️🧠🤖🦾🦿🖥️💾🟨🟩⬛🏁📋🧩🏛️🎭🛰️🔊🔉💡🛞🛠️📅📜🔌⚙️🚀🔋🗺️🔄🕹️🎮📱🌐💻🔑🚨📂📈🚥📊🏢🔗🛑📟"
    "]+", flags=re.UNICODE
)

def purge_emojis(directory):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(('.md', '.html', '.yaml', '.txt', '.example')):
                file_path = os.path.join(root, file)
                # Try UTF-8 encoding
                try:
                    with open(file_path, 'r', encoding='utf-8') as f:
                        content = f.read()
                except UnicodeDecodeError:
                    # Fallback for non-UTF8 files
                    with open(file_path, 'r', encoding='latin-1') as f:
                        content = f.read()
                
                new_content = emoji_pattern.sub('', content)
                
                if content != new_content:
                    with open(file_path, 'w', encoding='utf-8') as f:
                        f.write(new_content)
                    print(f"Purged emojis from: {file_path}")

if __name__ == "__main__":
    purge_emojis(".")
