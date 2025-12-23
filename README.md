
# Breakbeat
A Vertical Scrolling Rhythm Game (VSRG) similar to osu!mania, written in C++ using the OpenGL specificiation and various other libraries.

Contains charts converted from osu!mania.

# Gameplay
https://github.com/user-attachments/assets/7368f1c7-18f9-49bd-b388-94187896f5ad

# Support 
- Only works for Windows 64bit and 32bit
- Need a graphics card that supports opengl 3.3+
- Might not work for some integrated graphics cards due to bindless textures in use

# Instructions (Releases)

## Dependencies (Releases)
- **Microsoft Visual C++ Redistributable 2015–2022**  
  [Download Redistributable](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170)  

## Steps
1. The `.exe` is available in the **Releases** section.  
2. Download and extract the `breakbeat.zip` in the release. The zip contains the binary `.exe`.
3. The `charts.zip` in the release contains independent chart files. Extacting `breakbeat.zip` alone will render the  `breakbeat.exe` without ready charts.
- This is what the game chart selection screen will look life you have no charts:
 <img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/acae87e4-78e0-4b4c-8cca-25d706952297" />
 
4. To have ready to play charts, download `charts.zip` in the **Releases** sections, extract them and place them in the game folder. 
- With ready made charts in the game folder, the chart selection screen should now look like this:
 <img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/5a484ebe-54c3-4c6e-b308-d4a84a82399f" />

# Instructions (Build)

## Dependencies (Build)
- **CMake** (version 3.30+)  
  [Download CMake](https://cmake.org/download/)  

- **Microsoft Visual C++ Redistributable 2015–2022**  
  [Download Redistributable](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170)  

- **MSVC Build Tools** (needed to compile with CMake)  
  [Download Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/)  

## Build Steps
1. Install the **Microsoft C++ Redistributable 2015–2022**, **CMake**, and **MSVC Build Tools** if not already installed.  

2. In your desired folder, clone the repo by opening a terminal and run:
```bash
git clone https://github.com/TomObungu/breakbeat.git
cd breakbeat
```
3. In the terminal in the repo folder, run:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```
5. The executable `breakbeat.exe` will appear in the project root alongside the `.dll` files. Run it directly.
6. If you have `Visual Studio` installed, the `.sln` file will be in the `build` folder. Opening it will allow viewing of source code.

# Installation Issues
- If you recieve an error such as MSVCP140.dll is missing then it means you do not have Microsoft Visual C++ Redistributable 2015-2022.

# Known Bugs
- The text in the settings menu will show trailing zeros after the decimal point whilst editing scroll speed
- Creating a new chart in the chart editor may not always let you place notes in the chart nor will the grid lines show up
- Sometimes pressing enter twice whilst editing settings crashes the game
- Playing another chart after finishing a chart entirely will cause the chart to never advance to the scores page
- Trying to load into another chart after finishing a chart may cause the chart to text to be black and the song to not load
- The difficulty calculation of beatmaps is not accurate
