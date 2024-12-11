import os
from PIL import Image

def convert_png_to_bmp_with_transparency(directory):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.lower().endswith('.png'):
                png_path = os.path.join(root, file)
                bmp_path = os.path.splitext(png_path)[0] + '.bmp'

                # Open the PNG and ensure it has an alpha channel
                with Image.open(png_path) as img:
                    img = img.convert('RGBA')  # Ensure RGBA for transparency

                    # Save as BMP with a V5 header to include the alpha channel
                    img.save(bmp_path, format='BMP', bmp_info_header='BMPV5HEADER')
                print(f"Converted: {png_path} -> {bmp_path}")

# Example usage:
# convert_png_to_bmp_with_transparency('.')
if __name__ == "__main__":
    directory_to_search = '.'  # Replace with the directory you want to start from
    convert_png_to_bmp_with_transparency(directory_to_search)
