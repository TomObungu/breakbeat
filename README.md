
# Breakbeat
A Vertical Scrolling Rhythm Game (VSRG) similar to osu!mania, written in C++ using the OpenGL specificiation and various other libraries.

Contains charts converted from osu!mania.

# Gameplay
https://github.com/user-attachments/assets/7368f1c7-18f9-49bd-b388-94187896f5ad

# Dependencies
Microsoft Visual C++ Redistributable 2015-2022: https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170

# Instructions
1. Install the **Microsoft C++ Redistributable 2015–2022** if not already installed.
3. Clone the repo:
```bash
git clone https://github.com/TomObungu/breakbeat.git
cd breakbeat
```
4. Open a terminal in repo folder and run:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```
4. Make sure your resolution is at 1080p and the display scaling is at 100%
5. The executable breakbeat.exe will appear in the project root alongside the `.dll` files. Run it directly.

# Issues
If you recieve an error such as MSVCP140.dll is missing then it means you do not have Microsoft Visual C++ Redistributable 2015-2022. 