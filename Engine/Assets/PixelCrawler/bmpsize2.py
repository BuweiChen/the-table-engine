import os
from PIL import Image

def process_run_sheet(img):
    """Process run sheet by breaking into 64px chunks and removing first/last 16px of each."""
    width, height = img.size
    new_img = Image.new('RGBA', (192, height), (0, 0, 0, 0))
    
    # Process each 64-pixel chunk
    for i in range(6):  # 6 frames
        # Source coordinates (skip first 16px and last 16px of each 64px chunk)
        src_start = i * 64 + 16  # Skip first 16px of chunk
        src_end = (i * 64) + 48  # End before last 16px of chunk
        
        # Extract the middle 32 pixels from each chunk
        chunk = img.crop((src_start, 0, src_end, height))
        
        # Paste into new image
        new_img.paste(chunk, (i * 32, 0))
    
    return new_img

def process_png_and_save_as_bmp(directory):
    processed_files = []

    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.lower().endswith('.png'):
                full_path = os.path.join(root, file)
                
                # Check if this is a Run-Sheet file
                is_run_sheet = 'run-sheet' in file.lower()
                
                with Image.open(full_path) as img:
                    img = img.convert('RGBA')
                    width, height = img.size
                    
                    if is_run_sheet:
                        img = process_run_sheet(img)
                    
                    # Handle the height cropping for Heroes/Enemy folders
                    if ('Heroes' in root or 'Enemy' in root) and height == 64:
                        img = img.crop((0, height // 2, img.size[0], height))
                    
                    # Save as BMP
                    bmp_path = os.path.splitext(full_path)[0] + '.bmp'
                    img.save(bmp_path, format='BMP', bmp_info_header='BMPV5HEADER')
                    processed_files.append((bmp_path, img.size[0], img.size[1]))

    return processed_files

# Run the function on the current directory
processed = process_png_and_save_as_bmp('.')
for f, w, h in processed:
    print(f"File: {f} - Dimensions: {w}x{h}")