# Photo Editor

This is a simple photo editor application built using C++ and the SFML (Simple and Fast Multimedia Library). The application allows users to load images, apply various image processing commands (like grayscale, blur, and rotation), and save the modified images.

## Features

- Load images from the filesystem.
- Save edited images back to the filesystem.
- Apply image processing commands:
  - Grayscale
  - Blur
  - Rotate left/right
- Undo and redo commands.
- Zoom in and out functionalities.

## Installation

### Prerequisites

- C++ Compiler (e.g., g++, clang++)
- SFML library (version 2.5 or higher)

### Steps

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/photo-editor.git
   cd photo-editor
   ```
2. **Build the project**:
   Compile the source files using your preferred method (make, Visual Studio, etc.) ensuring to link the necessary SFML libraries.

3. **Run the application**:
   After building the project, navigate to the executable directory and run the executable.

## Usage

1. Open the application.
2. Click on the **"Select File"** button to load an image.
3. Apply image processing commands by clicking the corresponding buttons.
4. Save the modified image by clicking the **"Save File"** button.

## Commands

- **Grayscale**: Converts the loaded image to grayscale.
- **Blur**: Applies a blur effect to the loaded image.
- **Rotate Left**: Rotates the image 90 degrees counterclockwise.
- **Rotate Right**: Rotates the image 90 degrees clockwise.
- **Zoom In**: Increases the zoom level of the displayed image.
- **Zoom Out**: Decreases the zoom level of the displayed image.
- **Undo**: Reverses the last action taken.
- **Redo**: Reapplies the last undone action.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
