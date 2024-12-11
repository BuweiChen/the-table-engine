import os
from PIL import Image
import sys

def convert_png_to_bmp(directory="."):
    """
    Recursively converts all PNG files in the given directory and its subdirectories to BMP format.
    Preserves transparency and maintains the same dimensions.
    
    Args:
        directory (str): The starting directory path (defaults to current directory)
    """
    try:
        # Walk through directory
        for root, dirs, files in os.walk(directory):
            for file in files:
                if file.lower().endswith('.png'):
                    png_path = os.path.join(root, file)
                    bmp_path = os.path.splitext(png_path)[0] + '.bmp'
                    
                    print(f"Converting: {png_path}")
                    
                    try:
                        # Open PNG with transparency
                        with Image.open(png_path) as img:
                            # Convert to RGBA if not already
                            img = img.convert('RGBA')
                            
                            # Create a new image with white background
                            background = Image.new('RGBA', img.size, (255, 255, 255, 255))
                            
                            # Composite the image onto the background using alpha channel
                            composite = Image.alpha_composite(background, img)
                            
                            # Convert to RGB for BMP
                            rgb_img = composite.convert('RGB')
                            
                            # Save as BMP
                            rgb_img.save(bmp_path, 'BMP')
                            
                            print(f"Successfully converted to: {bmp_path}")
                    
                    except Exception as e:
                        print(f"Error converting {png_path}: {str(e)}")
                        continue

    except Exception as e:
        print(f"Error accessing directory {directory}: {str(e)}")
        return

if __name__ == "__main__":
    # Use command line argument for directory if provided, otherwise use current directory
    directory = sys.argv[1] if len(sys.argv) > 1 else "."
    
    print(f"Starting PNG to BMP conversion in directory: {directory}")
    convert_png_to_bmp(directory)
    print("Conversion process completed!")