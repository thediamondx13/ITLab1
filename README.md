# ITLab1 - Encryption Application

A Qt-based desktop application that implements classical encryption algorithms: **Vigenere** and **Playfair** (4 squares modification).

## How to Use

1. **Launch the application**

2. **Vigenere Cipher:**
	- Enter your plaintext in the input text area or select a file to input from
	- Enter your encryption key
	- Click "Encrypt" to encode or "Decrypt" to decode
	- Copy the result from the output field or save it to a file

3. **Playfair Cipher:**
   - Enter your plaintext in the input text area or select a file to input from
   - Provide four encryption keys
   - Click "Encrypt" to encode or "Decrypt" to decode
   - Copy the result from the output field or save it to a file

## Technical Details

- **Language:** C++ with Qt Framework
- **Build System:** Visual Studio (Visual C++)
- **Deployment:** 
  - Uses `windeployqt` to bundle Qt dependencies
  - Executable with dependencies is provided in x64/Debug

## Project Structure

- `include/` - Header files
  - `ITLab1.h` - Main application window
  - `Crypter.h` - Encryption algorithm implementations
- `src/` - Source files
  - `ITLab1.cpp` - GUI logic and event handling
  - `Crypter.cpp` - Vigenere and Playfair cipher implementations
- `ui/` - GUI files
  - `ITLab1.ui` - GUI logic and event handling
- `x64/` - build results for Windows x64

## Building the app yourself

1. Open `ITLab1.vcxproj` in Visual Studio
2. Build the solution
3. Run `windeployqt` on the built executable
4. Use Enigma Virtual Machine or similar apps to create a portable executable
Please do NOT distribute the app without source code