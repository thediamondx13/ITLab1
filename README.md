# ITLab1 - Encryption Application

A Qt-based desktop application that implements classical encryption algorithms: **Vigenere** and **Playfair** (with 4 tables modification).

## Features

### Vigenere Cipher
- Encrypt and decrypt text using the Vigenere cipher algorithm
- Support for both Russian and English alphabets
- Text input/output via GUI
- Save and load encrypted/decrypted text to/from files

### Playfair Cipher (4 Tables Modification)
- Encrypt and decrypt text using an enhanced Playfair cipher with 4 substitution tables
- Each table (top-left, top-right, bottom-left, bottom-right) uses a separate key
- Cleaner implementation compared to traditional single-table Playfair
- Save and load encrypted/decrypted text to/from files
- Support for multiple alphabet sets

## How to Use

1. **Launch the application**

2. **Vigenere Cipher:**
   - Enter your plaintext in the input text area
   - Enter your encryption key (will be automatically sanitized to remove non-alphabet characters)
   - Click "Encrypt" to encode or "Decrypt" to decode
   - Use "Load" and "Save" buttons to work with files

3. **Playfair Cipher:**
   - Enter your plaintext in the input text area
   - Provide four separate keys (one for each table: TL, TR, BL, BR)
   - Click "Encrypt" to encode or "Decrypt" to decode
   - Use "Load" and "Save" buttons to work with files

## Technical Details

- **Language:** C++ with Qt Framework
- **Build System:** Visual Studio (Visual C++)
- **Deployment:** 
  - Uses `windeployqt` to bundle Qt dependencies
  - Uses Enigma Virtual Machine for creating a single executable file
  - Final executable is provided in releases

## Project Structure

- `include/` - Header files
  - `ITLab1.h` - Main application window
  - `Crypter.h` - Encryption algorithm implementations
- `src/` - Source files
  - `ITLab1.cpp` - GUI logic and event handling
  - `Crypter.cpp` - Vigenere and Playfair cipher implementations

## Building

1. Open `ITLab1.vcxproj` in Visual Studio
2. Build the solution
3. For deployment, run `windeployqt` on the built executable and then use Enigma Virtual Machine to create the final distributable executable