import os
from PIL import Image

def process_png_and_save_as_bmp(directory):
    processed_files = []

    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.lower().endswith('.png'):
                full_path = os.path.join(root, file)
                with Image.open(full_path) as img:
                    # Ensure we have an alpha channel
                    img = img.convert('RGBA')
                    width, height = img.size

                    # Only crop if in 'Heroes' or 'Enemy' and the height is 64
                    if ('Heroes' in root or 'Enemy' in root) and height == 64:
                        # Crop to keep only the bottom half
                        bottom_half = img.crop((0, height // 2, width, height))
                        
                        # Construct BMP output path
                        bmp_path = os.path.splitext(full_path)[0] + '.bmp'

                        # Save as BMP with a V5 header to include alpha channel
                        bottom_half.save(bmp_path, format='BMP', bmp_info_header='BMPV5HEADER')

                        processed_files.append((bmp_path, width, height // 2))
                    else:
                        # If the condition isn't met, you can either skip or still convert:
                        # In case you want to save as BMP anyway (just remove the else block if not):
                        bmp_path = os.path.splitext(full_path)[0] + '.bmp'
                        img.save(bmp_path, format='BMP', bmp_info_header='BMPV5HEADER')
                        processed_files.append((bmp_path, width, height))

    return processed_files

# Run the function on the current directory
processed = process_png_and_save_as_bmp('.')
for f, w, h in processed:
    print(f"File: {f} - Dimensions: {w}x{h}")
