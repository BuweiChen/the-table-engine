import os
from PIL import Image

def convert_png_to_32bit_bmp(directory):
    """
    Recursively traverse the directory and convert all .png files to 32-bit .bmp,
    preserving transparency.
    
    Args:
        directory (str): The path to the root directory to start the recursion.
    """
    for root, _, files in os.walk(directory):
        for file in files:
            if file.lower().endswith('.png'):
                file_path = os.path.join(root, file)
                new_file_path = os.path.splitext(file_path)[0] + ".bmp"
                try:
                    with Image.open(file_path) as img:
                        if img.mode != "RGBA":
                            img = img.convert("RGBA")  # Ensure it has an alpha channel
                        img.save(new_file_path, "BMP")
                        print(f"Converted: {file_path} -> {new_file_path}")
                except Exception as e:
                    print(f"Failed to convert {file_path}: {e}")


convert_png_to_32bit_bmp("./Engine/Assets")
