import tkinter as tk
from tkinter import filedialog, messagebox, ttk
import time
from tkinter import simpledialog
from PIL import Image, ImageTk
import json
import os
import subprocess

class AddItemPopup(tk.Toplevel):
    def __init__(self, parent, title, item_type, existing_data=None):
        super().__init__(parent)
        self.dynamic_properties = {}
        self.parent = parent
        self.item_type = item_type  # "structure" or "entity"
        self.existing_data = existing_data
        self.title(title)
        self.geometry("700x650")

        self.cols_var = tk.IntVar(value=1)
        self.rows_var = tk.IntVar(value=1)
        self.animation_time = tk.IntVar(value=100)
        self.length_var = tk.IntVar(value=32)
        self.width_var = tk.IntVar(value=32)
        self.top_left_x = tk.IntVar(value=0)
        self.top_left_y = tk.IntVar(value=0)
        self.size_width = tk.IntVar(value=0)
        self.size_height = tk.IntVar(value=0)

        tk.Label(self, text="Name:").pack(anchor="w", padx=10, pady=5)
        self.name_var = tk.StringVar()
        self.name_entry = tk.Entry(self, textvariable=self.name_var)
        self.name_entry.pack(fill="x", padx=10)

        tk.Label(self, text="Bitmap File (BMP):").pack(anchor="w", padx=10, pady=5)
        self.file_var = tk.StringVar()
        file_frame = tk.Frame(self)
        file_frame.pack(fill="x", padx=10)
        self.file_entry = tk.Entry(file_frame, textvariable=self.file_var)
        self.file_entry.pack(side="left", fill="x", expand=True)
        tk.Button(file_frame, text="Browse", command=self.browse_file).pack(side="left")

        pos_frame = tk.Frame(self)
        pos_frame.pack(fill="x", padx=10, pady=10)

        tk.Label(pos_frame, text="Columns:").grid(
            row=0, column=0, sticky="w", padx=10, pady=5
        )
        tk.Entry(pos_frame, textvariable=self.cols_var).grid(
            row=0, column=1, sticky="w", padx=10, pady=5
        )
        self.cols_var.trace_add(
            "write", lambda *args: self.preview_image(self.file_var.get())
        )

        tk.Label(pos_frame, text="Rows:").grid(
            row=0, column=2, sticky="e", padx=10, pady=5
        )
        tk.Entry(pos_frame, textvariable=self.rows_var).grid(
            row=0, column=3, sticky="e", padx=10, pady=5
        )
        self.rows_var.trace_add(
            "write", lambda *args: self.preview_image(self.file_var.get())
        )

        tk.Label(pos_frame, text="Time to complete animation (s):").grid(
            row=1, column=0, sticky="w", padx=10, pady=5
        )
        tk.Entry(pos_frame, textvariable=self.animation_time).grid(
            row=1, column=1, sticky="w", padx=10, pady=5
        )

        screen_frame = tk.Frame(self)
        screen_frame.pack(fill="x", padx=10, pady=10)

        tk.Label(screen_frame, text="Screen width (px):").grid(
            row=0, column=0, sticky="w", padx=10, pady=5
        )
        tk.Entry(screen_frame, textvariable=self.length_var).grid(
            row=0, column=1, sticky="w", padx=10, pady=5
        )

        tk.Label(screen_frame, text="Screen height (px):").grid(
            row=0, column=2, sticky="e", padx=10, pady=5
        )
        tk.Entry(screen_frame, textvariable=self.width_var).grid(
            row=0, column=3, sticky="e", padx=10, pady=5
        )

        # image preview
        self.preview_canvas = tk.Canvas(self, width=200, height=200)
        self.preview_canvas.pack(fill="both", padx=20)

        # Create a frame to hold the form
        form_frame = tk.Frame(self)
        form_frame.pack(fill="x", padx=10, pady=10)

        # TopLeft X
        tk.Label(form_frame, text="Sprite X:").grid(
            row=0, column=0, sticky="w", padx=5, pady=5
        )
        tk.Entry(form_frame, textvariable=self.top_left_x).grid(
            row=0, column=1, sticky="w", padx=10, pady=5
        )
        self.top_left_x.trace_add(
            "write", lambda *args: self.preview_image(self.file_var.get())
        )

        # TopLeft Y
        tk.Label(form_frame, text="Sprite Y:").grid(
            row=0, column=2, sticky="e", padx=5, pady=5
        )
        tk.Entry(form_frame, textvariable=self.top_left_y).grid(
            row=0, column=3, sticky="e", padx=10, pady=5
        )
        self.top_left_y.trace_add(
            "write", lambda *args: self.preview_image(self.file_var.get())
        )

        # Size width
        tk.Label(form_frame, text="Sprite width (px):").grid(
            row=1, column=0, sticky="w", padx=5, pady=5
        )
        tk.Entry(form_frame, textvariable=self.size_width).grid(
            row=1, column=1, sticky="w", padx=10, pady=5
        )
        self.size_width.trace_add(
            "write", lambda *args: self.preview_image(self.file_var.get())
        )

        # Size height
        tk.Label(form_frame, text="Sprite height (px):").grid(
            row=1, column=2, sticky="e", padx=5, pady=5
        )
        tk.Entry(form_frame, textvariable=self.size_height).grid(
            row=1, column=3, sticky="e", padx=10, pady=5
        )
        self.size_height.trace_add(
            "write", lambda *args: self.preview_image(self.file_var.get())
        )

        btn_frame = tk.Frame(self)
        btn_frame.pack(fill="x", pady=10)
        tk.Button(
            btn_frame, text="GameObject Properties", command=self.open_entity_properties
        ).pack(side="left", padx=10)
        tk.Button(btn_frame, text="OK", command=self.confirm).pack(
            side="right", padx=10
        )
        tk.Button(btn_frame, text="Cancel", command=self.destroy).pack(side="right")

        # If editing existing data
        if self.existing_data:
            self.name_var.set(self.existing_data["name"])
            self.file_var.set(self.existing_data["file"])
            self.cols_var.set(self.existing_data["columns"])
            self.rows_var.set(self.existing_data["rows"])
            self.animation_time.set(self.existing_data["animation_time"])
            self.top_left_x.set(self.existing_data["top_left_x"])
            self.top_left_y.set(self.existing_data["top_left_y"])
            self.size_width.set(self.existing_data["size_width"])
            self.size_height.set(self.existing_data["size_height"])
            self.length_var.set(self.existing_data["length"])
            self.width_var.set(self.existing_data["width"])
            self.dynamic_properties = self.existing_data["properties"]

    def browse_file(self):
        file_path = filedialog.askopenfilename(filetypes=[("BMP Files", "*.bmp")])
        if file_path:
            self.file_var.set(file_path)
            self.preview_image(file_path, True)

    def confirm(self):
        name = self.name_var.get()
        file = self.file_var.get()
        cols = self.cols_var.get()
        rows = self.rows_var.get()
        animation_time = self.animation_time.get()
        size_width = self.size_width.get()
        size_height = self.size_height.get()
        top_left_x = self.top_left_x.get()
        top_left_y = self.top_left_y.get()
        length = self.length_var.get()
        width = self.width_var.get()
        property = self.dynamic_properties

        editing = self.existing_data is not None
        print(self.item_type)
        item_type = (
            self.parent.structures
            if self.item_type == "structure"
            else self.parent.entities
        )

        if editing:
            old_name = self.existing_data["name"] if self.existing_data else ""
            if name != old_name and name in item_type:
                messagebox.showerror(
                    "Error", "A gameobject with that name already exists."
                )
                return
        elif name in self.parent.entities:
            messagebox.showerror("Error", "A gameobject with that name already exists.")
            return
        elif name in self.parent.structures:
            messagebox.showerror("Error", "A gameobject with that name already exists.")
            return
        
        if property == {}:
            messagebox.showwarning("Incomplete", "Please select gameobject properties")
            return
        
        if not name or not file:
            messagebox.showwarning(
                "Incomplete", "Please provide a name and a bmp file."
            )
            return

        # Load the BMP and slice into frames
        try:
            img = Image.open(file)
        except Exception as e:
            messagebox.showerror("Error", f"Failed to load image: {e}")
            return

        frame_width = size_width // cols
        frame_height = size_height // rows

        frames = []
        for r in range(rows):
            for c in range(cols):
                frame = img.crop(
                    (
                        c * frame_width + top_left_x,
                        r * frame_height + top_left_y,
                        (c + 1) * frame_width + top_left_x,
                        (r + 1) * frame_height + top_left_y,
                    )
                )

                frame = frame.resize((length, width), Image.LANCZOS)
                frames.append(ImageTk.PhotoImage(frame))

        data = {
            "name": name,
            "file": file,
            "columns": cols,
            "rows": rows,
            "animation_time": animation_time,
            "length": length,
            "width": width,
            "top_left_x": top_left_x,
            "top_left_y": top_left_y,
            "size_width": size_width,
            "size_height": size_height,
            "frames": frames,
            "properties": property,  # Include dynamic properties
        }

        self.parent.add_item_callback(
            self.item_type, data, self.existing_data is not None
        )
        self.destroy()

    def preview_image(self, file_path, reset=False):
        # add red grid lines based on cols and rows by defautl set both to 1

        cols, rows = 1, 1
        size_width, size_height = 0, 0
        top_left_x, top_left_y = 0, 0

        try:
            if not reset:
                cols = int(self.cols_var.get())
                rows = int(self.rows_var.get())
                top_left_x = self.top_left_x.get()
                top_left_y = self.top_left_y.get()
                size_width = int(self.size_width.get())
                size_height = int(self.size_height.get())
            else:
                self.cols_var.set(1)
                self.rows_var.set(1)
                self.top_left_x.set(0)
                self.top_left_y.set(0)
                self.size_width.set(0)
                self.size_height.set(0)
        except:
            return

        try:
            img = Image.open(file_path)
            if size_width == 0:
                self.size_width.set(img.width)
            if size_height == 0:
                self.size_height.set(img.height)
            w, h = img.size
            if w > h:
                self.scale = 200 / w
            else:
                self.scale = 200 / h

            size_width = self.size_width.get() * self.scale
            size_height = self.size_height.get() * self.scale
            top_left_x = self.top_left_x.get() * self.scale
            top_left_y = self.top_left_y.get() * self.scale

            img = img.resize((int(w * self.scale), int(h * self.scale)), Image.LANCZOS)
            img_tk = ImageTk.PhotoImage(img)
            self.preview_canvas.delete("all")

            # anchor to the center of the canvas
            self.preview_canvas.create_image(0, 0, anchor="nw", image=img_tk)
            self.preview_canvas.image = img_tk

            w, h = img.size
            self.preview_canvas.create_line(
                top_left_x,
                top_left_y,
                top_left_x,
                top_left_y + size_height,
                fill="blue",
                width=3,
            )
            self.preview_canvas.create_line(
                top_left_x + size_width,
                top_left_y,
                top_left_x + size_width,
                top_left_y + size_height,
                fill="blue",
                width=3,
            )

            self.preview_canvas.create_line(
                top_left_x,
                top_left_y,
                top_left_x + size_width,
                top_left_y,
                fill="blue",
                width=3,
            )
            self.preview_canvas.create_line(
                top_left_x,
                top_left_y + size_height,
                top_left_x + size_width,
                top_left_y + size_height,
                fill="blue",
                width=3,
            )

            # Draw vertical lines
            for col in range(1, cols):
                dx = (size_width * col) // cols
                self.preview_canvas.create_line(
                    top_left_x + dx,
                    top_left_y,
                    top_left_x + dx,
                    top_left_y + size_height,
                    fill="red",
                    width=1,
                )

            # Draw horizontal lines
            for row in range(1, rows):
                dy = size_height * row // rows
                self.preview_canvas.create_line(
                    top_left_x,
                    top_left_y + dy,
                    top_left_x + size_width,
                    top_left_y + dy,
                    fill="red",
                    width=1,
                )

        except Exception as e:
            messagebox.showerror("Error", f"Failed to load image: {e}")

    # Todo: add GameObject Properties - type + specific properties (health, speed, etc.) depending on type
    def open_entity_properties(self):
        self.entity_properties = GameObjectPropertiesPopup(self, self.item_type)
        self.entity_properties.protocol("WM_DELETE_WINDOW", self.on_popup_close)

    def on_popup_close(self):
        self.entity_properties.destroy()


class GameObjectPropertiesPopup(tk.Toplevel):
    def __init__(
        self,
        parent,
        object_type,
        config_file=os.path.join(os.path.dirname(__file__), "config.json"),
    ):
        super().__init__(parent)
        self.title("GameObject Properties")
        self.geometry("400x700")
        self.parent = parent
        self.object_type = object_type.capitalize()
        self.config_file = config_file
        self.fields = {}
        self.selected_type = tk.StringVar()  # To store the selected type

        # Load config
        self.config_data = self.load_config()

        if self.config_data == {}:
            self.selected_type.set(self.parent.dynamic_properties["type"])

        # Create UI
        self.create_type_dropdown()  # Dropdown to select the type
        self.dynamic_frame = tk.Frame(self)
        self.dynamic_frame.pack(fill="x", padx=10, pady=10)

        # Add confirm and cancel buttons
        btn_frame = tk.Frame(self)
        btn_frame.pack(fill="x", pady=10)
        tk.Button(btn_frame, text="OK", command=self.confirm).pack(
            side="right", padx=10
        )
        tk.Button(btn_frame, text="Cancel", command=self.destroy).pack(side="right")

        # Automatically populate fields if type is already selected
        if "type" in self.parent.dynamic_properties:
            self.selected_type.set(self.parent.dynamic_properties["type"])
            self.update_dynamic_fields()

    def load_config(self):
        """Load the configuration file."""
        if not os.path.exists(self.config_file):
            messagebox.showerror("Error", f"Config file {self.config_file} not found.")
            self.destroy()
            return {}
        try:
            with open(self.config_file, "r") as file:
                return json.load(file)
        except json.JSONDecodeError as e:
            messagebox.showerror("Error", f"Failed to parse config file: {e}")
            self.destroy()
            return {}

    def create_type_dropdown(self):
        """Create a dropdown to select the object type."""
        if self.object_type not in self.config_data:
            messagebox.showerror(
                "Error", f"Object type '{self.object_type}' not found in config."
            )
            self.destroy()
            return

        obj_types = list(self.config_data[self.object_type].keys())
        if not obj_types:
            messagebox.showerror(
                "Error", f"No types found for object type '{self.object_type}'."
            )
            self.destroy()
            return

        tk.Label(self, text="Select Type:", font=("Arial", 12)).pack(
            anchor="w", padx=10, pady=5
        )
        dropdown = ttk.Combobox(self, textvariable=self.selected_type, values=obj_types)
        dropdown.pack(fill="x", padx=10, pady=5)
        dropdown.bind("<<ComboboxSelected>>", self.update_dynamic_fields)

    def update_dynamic_fields(self, event=None):
        """Update the fields based on the selected type."""
        # Clear the current fields
        for widget in self.dynamic_frame.winfo_children():
            widget.destroy()
        self.fields = {}

        selected_type = self.selected_type.get()
        if not selected_type or selected_type not in self.config_data[self.object_type]:
            return

        # Populate fields for the selected type
        properties = self.config_data[self.object_type][selected_type]
        prepopulated_data = self.parent.dynamic_properties.get("data", {}).get(
            selected_type, {}
        )

        # if properties is a list, create a label saying "No properties"
        if len(properties) == 0:
            tk.Label(self.dynamic_frame, text="No special properties").pack(
                fill="x", padx=10, pady=5
            )
            return

        for prop_name, prop_type in properties.items():
            field_frame = tk.Frame(self.dynamic_frame)
            field_frame.pack(fill="x", padx=10, pady=5)

            tk.Label(field_frame, text=prop_name).pack(side="left")
            var = None
            # check if prop_type is type int
            if type(prop_type) == int:
                var = tk.IntVar(value=prepopulated_data.get(prop_name, prop_type))
                tk.Entry(field_frame, textvariable=var).pack(
                    side="right", fill="x", expand=True
                )
                
            elif type(prop_type) == float:
                # align text to the right
                var = tk.DoubleVar(value=prepopulated_data.get(prop_name, prop_type))
                tk.Entry(field_frame, textvariable=var).pack(
                    side="right", fill="x", expand=True
                )
            elif prop_type == "str":
                var = tk.StringVar(value=prepopulated_data.get(prop_name, ""))
                tk.Entry(field_frame, textvariable=var).pack(
                    side="right", fill="x", expand=True
                )
            elif type(prop_type) == bool:
                var = tk.BooleanVar(value=prepopulated_data.get(prop_name, prop_type))
                tk.Checkbutton(field_frame, variable=var).pack(side="right")
            elif prop_type == "checkbox_with_all_objects":
                self.create_checkboxes_for_objects(
                    field_frame,
                    prop_name,
                    selected_type,
                    prepopulated_data.get(prop_name, {}),
                )
            else:
                var = tk.StringVar(value=prepopulated_data.get(prop_name, ""))
                tk.Entry(field_frame, textvariable=var).pack(
                    side="right", fill="x", expand=True
                )   

            if prepopulated_data is not None and not {}:
                self.parent.dynamic_properties["data"][selected_type] = var

            if prop_type != "checkbox_with_all_objects":
                self.fields[prop_name] = var

    def create_checkboxes_for_objects(
        self, parent_frame, prop_name, selected_type, prepopulated_data
    ):
        """Create checkboxes for all object types defined in the config.json."""
        # Load all object types from the config.json
        object_types = []
        if "Structure" in self.config_data:
            object_types.extend(self.config_data["Structure"].keys())
        if "Entity" in self.config_data:
            object_types.extend(self.config_data["Entity"].keys())

        # Create a checkbox for each object type
        for obj_name in object_types:
            print(selected_type, obj_name)
            if obj_name == "Player" and selected_type == "Player":
                continue
            default_bool = obj_name == "Wall" or selected_type == "Wall"
            checkbox_var = tk.BooleanVar(
                value=prepopulated_data.get(obj_name, default_bool)
            )
            checkbox = tk.Checkbutton(
                parent_frame, text=obj_name, variable=checkbox_var
            )
            checkbox.pack(anchor="w", padx=20)
            if prop_name not in self.fields:
                self.fields[prop_name] = {}
            self.fields[prop_name][obj_name] = checkbox_var

    def confirm(self):
        """Confirm the selection and store data."""
        selected_type = self.selected_type.get()

        if not selected_type:
            messagebox.showerror("Error", "Please select a type.")
            return

        # Initialize or update the dynamic_properties dictionary
        if "data" not in self.parent.dynamic_properties:
            self.parent.dynamic_properties["data"] = {}

        # Store the selected type
        self.parent.dynamic_properties["type"] = selected_type

        # Collect the field values for the selected type
        properties = {}
        for key, value in self.fields.items():
            if isinstance(value, dict):  # Handle nested dictionary for checkboxes
                properties[key] = {sub_key: var.get() for sub_key, var in value.items()}
            else:
                properties[key] = value.get()

        # Save the properties under the selected type
        self.parent.dynamic_properties["data"][selected_type] = properties

        # Close the popup
        self.destroy()


class LevelEditorApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Level Editor")
        self.geometry("1200x900")
        self.popup_window = None

        # Data storage
        self.structures = {}  # name -> data dict
        self.entities = {}  # name -> data dict
        self.levels = []  # list of dict { "canvas": canvas_widget, "items": [(item_name, x, y, image_id), ...] }

        self.current_level_index = -1

        # Menu Bar
        self.menubar = tk.Menu(self)

        # File
        self.file = tk.Menu(self.menubar, tearoff=0)
        self.menubar.add_cascade(label="File", menu=self.file)
        self.file.add_command(label="Export", command=self.export)

        # Start Game
        self.start_game = tk.Menu(self.menubar, tearoff=0)
        self.menubar.add_cascade(label="Run", menu=self.start_game)
        self.start_game.add_command(label="Run Game", command=self.execute_game)
        self.start_game.add_command(label="Run Demo", command=self.execute_demo)

        self.config(menu=self.menubar)

        # For animating images
        self.current_time = 0
        self.current_frame = 0
        self.last_time = -1000

        # for saving selected name
        self.last_sel = None

        # Frames
        self.left_frame = tk.Frame(self, width=200, bg="#ddd")
        self.left_frame.pack(side="left", fill="y")

        # Structures UI
        tk.Label(
            self.left_frame, text="Structures", font=("Arial", 14, "bold"), bg="#ddd"
        ).pack(anchor="nw", padx=5, pady=5)
        btn_frame_struct = tk.Frame(self.left_frame, bg="#ddd")
        btn_frame_struct.pack(fill="x")
        tk.Button(
            btn_frame_struct,
            text="Add",
            command=lambda: self.show_add_popup("structure"),
        ).pack(side="left", padx=5, pady=5)
        tk.Button(
            btn_frame_struct, text="Delete", command=self.delete_selected_structure
        ).pack(side="left", padx=5, pady=5)
        self.structures_listbox = tk.Listbox(self.left_frame)
        self.structures_listbox.pack(fill="both", expand=True, padx=5, pady=(0, 5))
        self.structures_listbox.bind(
            "<Double-Button-1>", lambda e: self.edit_selected_item("structure")
        )

        # Entities UI
        tk.Label(
            self.left_frame, text="Entities", font=("Arial", 14, "bold"), bg="#ddd"
        ).pack(anchor="nw", padx=5, pady=5)
        btn_frame_entity = tk.Frame(self.left_frame, bg="#ddd")
        btn_frame_entity.pack(fill="x")
        tk.Button(
            btn_frame_entity, text="Add", command=lambda: self.show_add_popup("entity")
        ).pack(side="left", padx=5, pady=5)
        tk.Button(
            btn_frame_entity, text="Delete", command=self.delete_selected_entity
        ).pack(side="left", padx=5, pady=5)
        self.entities_listbox = tk.Listbox(self.left_frame)
        self.entities_listbox.pack(fill="both", expand=True, padx=5, pady=(0, 5))
        self.entities_listbox.bind(
            "<Double-Button-1>", lambda e: self.edit_selected_item("entity")
        )

        # Drag and drop setup
        self.drag_data = {"type": None, "name": None, "item_index": None, "image": None}
        self.bind("<ButtonRelease-1>", self.on_mouse_release)
        self.bind("<Motion>", self.on_mouse_move)
        self.left_frame.bind_all("<B1-Motion>", self.on_mouse_drag)
        self.entities_listbox.bind("<Button-1>", lambda e: self.start_drag("entity", e))
        self.structures_listbox.bind(
            "<Button-1>", lambda e: self.start_drag("structure", e)
        )

        # Top Right Frame for levels
        self.right_frame = tk.Frame(self, width=200, bg="#ddd")
        self.right_frame.pack(side="right", fill="y")
        tk.Label(
            self.right_frame, text="Levels", font=("Arial", 14, "bold"), bg="#ddd"
        ).pack(anchor="nw", padx=5, pady=5)
        btn_frame_levels = tk.Frame(self.right_frame, bg="#ddd")
        btn_frame_levels.pack(fill="x", padx=5, pady=5)
        tk.Button(btn_frame_levels, text="Add", command=self.add_level).pack(
            side="left", padx=5
        )
        tk.Button(
            btn_frame_levels, text="Delete", command=self.delete_selected_level
        ).pack(side="left", padx=5)

        self.levels_listbox = tk.Listbox(self.right_frame)
        self.levels_listbox.pack(fill="both", expand=True, padx=5, pady=(0, 5))
        self.levels_listbox.bind("<<ListboxSelect>>", lambda e: self.switch_level())

        # Main Canvas Frame (for levels)
        self.center_frame = tk.Frame(self, bg="#eee", width=800, height=800)
        self.center_frame.pack(side="left", fill="both", expand=True)
        self.center_frame.pack_propagate(False)

        # Animate images
        self.animate_images()

        # Initially add one level
        self.add_level()

    def add_item_callback(self, item_type, data, editing=False):
        """Called when popup confirms adding/editing an item."""
        if item_type == "structure":
            if editing:
                sel = self.last_sel
                if sel:
                    old_name = self.structures_listbox.get(sel[0])
                    del self.structures[old_name]
                    self.structures_listbox.delete(sel[0])
            name = data["name"]
            self.structures[name] = data
            self.structures_listbox.insert("end", name)

        else:  # entity
            if editing:
                sel = self.last_sel
                if sel:
                    old_name = self.entities_listbox.get(sel[0])
                    del self.entities[old_name]
                    self.entities_listbox.delete(sel[0])
            name = data["name"]
            # Include dynamic properties
            dynamic_properties = data.get("properties", {})
            self.entities[name] = {**data, **dynamic_properties}
            self.entities_listbox.insert("end", name)

    def show_add_popup(self, item_type):
        if self.popup_window and self.popup_window.winfo_exists():
            self.popup_window.lift()
            return
        self.popup_window = AddItemPopup(
            self, f"Add {item_type.capitalize()}", item_type
        )
        self.popup_name = None
        self.popup_window.protocol("WM_DELETE_WINDOW")

    def edit_selected_item(self, item_type):
        if self.popup_window and self.popup_window.winfo_exists():
            self.popup_window.destroy()

        if item_type == "structure":
            sel = self.structures_listbox.curselection()
            if not sel:
                return
            self.last_sel = sel
            name = self.structures_listbox.get(sel[0])
            data = self.structures[name]
        else:
            sel = self.entities_listbox.curselection()
            if not sel:
                return
            self.last_sel = sel
            name = self.entities_listbox.get(sel[0])
            data = self.entities[name]

        self.popup_window = AddItemPopup(
            self, f"Edit {item_type.capitalize()}", item_type, existing_data=data
        )
        self.popup_window.lift()
        self.popup_window.protocol("WM_DELETE_WINDOW", self.on_popup_close)

    def delete_selected_structure(self):
        sel = self.structures_listbox.curselection()
        if not sel:
            return
        name = self.structures_listbox.get(sel[0])
        del self.structures[name]
        self.structures_listbox.delete(sel[0])
        self.remove_all_instances(name)

    def delete_selected_entity(self):
        sel = self.entities_listbox.curselection()
        if not sel:
            return
        name = self.entities_listbox.get(sel[0])
        del self.entities[name]
        self.entities_listbox.delete(sel[0])
        self.remove_all_instances(name)

    def remove_all_instances(self, name):
        """Remove all instances of the given structure/entity from all levels."""
        for level_data in self.levels:
            new_items = []
            for itm_name, x, y, img_id in level_data["items"]:
                if itm_name == name:
                    level_data["canvas"].delete(img_id)
                else:
                    new_items.append((itm_name, x, y, img_id))
            level_data["items"] = new_items

    def start_drag(self, item_type, event):
        if self.popup_window and self.popup_window.winfo_exists():
            self.popup_window.destroy()

        listbox = (
            self.structures_listbox
            if item_type == "structure"
            else self.entities_listbox
        )
        index = listbox.nearest(event.y)
        if index < 0:
            return
        name = listbox.get(index)

        self.drag_data["type"] = item_type
        self.drag_data["name"] = name
        self.drag_data["item_index"] = index

        if item_type == "structure":
            frames = self.structures[name]["frames"]
        else:
            frames = self.entities[name]["frames"]

        self.drag_data["image"] = frames[self.current_frame] if frames else None
        self.drag_data["image_id"] = None  # Initialize the image ID for temporary image

    def on_mouse_drag(self, event):
        if self.drag_data["type"]:
            canvas = self.levels[self.current_level_index]["canvas"]

            # Get raw coordinates relative to the canvas
            canvas_x = event.x_root - canvas.winfo_rootx()
            canvas_y = event.y_root - canvas.winfo_rooty()

            # Get the object's specified size
            if self.drag_data["type"] == "structure":
                obj_data = self.structures[self.drag_data["name"]]
            else:
                obj_data = self.entities[self.drag_data["name"]]

            # Calculate top-left alignment for the image
            snapped_x = canvas_x
            snapped_y = canvas_y

            # Create or update the temporary image
            if self.drag_data.get("image_id"):
                canvas.coords(self.drag_data["image_id"], snapped_x, snapped_y)
            else:
                self.drag_data["image_id"] = canvas.create_image(
                    snapped_x, snapped_y, image=self.drag_data["image"], anchor="nw"
                )

    def on_mouse_move(self, event):
        # level_data = self.levels[self.current_level_index]
        # print(len(level_data["items"]))
        pass

    def on_mouse_release(self, event):
        if self.drag_data["type"]:
            if self.current_level_index >= 0:
                level_data = self.levels[self.current_level_index]
                canvas = level_data["canvas"]

                # Get raw coordinates relative to the canvas
                canvas_x = event.x_root - canvas.winfo_rootx()
                canvas_y = event.y_root - canvas.winfo_rooty()

                # Get the object's specified size
                if self.drag_data["type"] == "structure":
                    obj_data = self.structures[self.drag_data["name"]]
                else:
                    obj_data = self.entities[self.drag_data["name"]]

                # Snap to the nearest grid point (align top-right corner of image)
                grid_size = 32
                snapped_x = round(canvas_x / grid_size) * grid_size
                snapped_y = round(canvas_y / grid_size) * grid_size

                # Ensure snapped coordinates are within bounds
                if 0 <= canvas_x <= 800 and 0 <= canvas_x <= 800:
                    # Place the final image at the snapped position
                    img_id = canvas.create_image(
                        snapped_x, snapped_y, image=self.drag_data["image"], anchor="nw"
                    )
                    level_data["items"].append(
                        (self.drag_data["name"], snapped_x, snapped_y, img_id, 0, 0)
                    )

                # Remove the temporary drag image
                if self.drag_data.get("image_id"):
                    canvas.delete(self.drag_data["image_id"])

            # Reset drag data
            self.drag_data = {
                "type": None,
                "name": None,
                "item_index": None,
                "image": None,
                "image_id": None,
            }

    def animate_images(self):
        for level_data in self.levels:
            for name, data in self.structures.items():
                frames = data["frames"]
                if frames and len(frames) > 1:
                    for i in range(len(level_data["items"])):
                        itm_name, x, y, img_id, frame_index, last_frame_time = (
                            level_data["items"][i]
                        )
                        if itm_name == name:
                            if (
                                time.time() - last_frame_time
                                > data["animation_time"] / 1000
                            ):
                                last_frame_time = time.time()
                                frame_index = (frame_index + 1) % len(frames)
                            level_data["items"][i] = (
                                itm_name,
                                x,
                                y,
                                img_id,
                                frame_index,
                                last_frame_time,
                            )
                            self.levels[self.current_level_index]["canvas"].itemconfig(
                                img_id, image=frames[frame_index]
                            )
        self.after(50, self.animate_images)

    def add_level(self):
        level_frame = tk.Frame(self.center_frame, width=800, height=800, bg="white")
        level_frame.place(x=0, y=0)
        canvas = tk.Canvas(level_frame, bg="white", width=800, height=800)
        canvas.bind("<Button-1>", self.delete_gameobject)
        canvas.pack(fill="both", expand=True)

        # Draw grid
        for x in range(0, 801, 32):
            canvas.create_line(x, 0, x, 800, fill="#ccc")
        for y in range(0, 801, 32):
            canvas.create_line(0, y, 800, y, fill="#ccc")

        self.levels.append({"frame": level_frame, "canvas": canvas, "items": []})
        self.levels_listbox.insert("end", f"Level {len(self.levels)}")

        new_idx = len(self.levels) - 1
        self.levels_listbox.selection_set(new_idx)
        self.switch_level()
        self.current_level_index = new_idx

    def switch_level(self):
        sel = self.levels_listbox.curselection()
        if not sel:
            return
        idx = sel[0]
        new_frame = self.levels[idx]["frame"]
        new_frame.tkraise()
        self.current_level_index = idx

    def delete_selected_level(self):
        sel = self.levels_listbox.curselection()
        if not sel:
            return
        idx = sel[0]
        level_data = self.levels[idx]
        level_data["canvas"].destroy()
        del self.levels[idx]
        self.levels_listbox.delete(idx)

        # Rename levels
        for i in range(len(self.levels)):
            self.levels_listbox.delete(i)
            self.levels_listbox.insert(i, f"Level {i+1}")

        if len(self.levels) == 0:
            self.current_level_index = -1
        else:
            new_idx = min(idx, len(self.levels) - 1)
            self.levels_listbox.selection_clear(0, "end")
            self.levels_listbox.selection_set(new_idx)
            self.switch_level()

    def export(self):
        """Export the project data as a JSON file."""
        # Ask the user for a file name
        # file_name = simpledialog.askstring(
        #     "Export Project",
        #     "Enter a name for the export file (without extension):",
        # )
        file_name = "game"
        if not file_name:
            messagebox.showerror("Export Failed", "File name cannot be empty.")
            return

        # Ensure the output directory exists
        output_dir = os.path.join(os.path.dirname(__file__), "game_json_output")
        os.makedirs(output_dir, exist_ok=True)

        # Create the file path
        file_path = os.path.join(output_dir, f"{file_name}.json")

        # Helper function to remove the 'frames' field
        def sanitize_object_data(objects):
            sanitized = {}
            for name, props in objects.items():
                sanitized[name] = {
                    key: value for key, value in props.items() if key != "frames"
                }
            return sanitized

        # Prepare the data for export
        data = {
            "object_definitions": {
                "structures": sanitize_object_data(self.structures),
                "entities": sanitize_object_data(self.entities),
            },
            "levels": [],
        }

        for level in self.levels:
            level_data = {"objects": []}
            for obj_name, x, y, img_id, _, _ in level["items"]:
                level_data["objects"].append(
                    {
                        "name": obj_name,
                        "x": x,
                        "y": y,
                        "type": "structure"
                        if obj_name in self.structures
                        else "entity",
                    }
                )
            data["levels"].append(level_data)

        # Save the JSON file
        try:
            with open(file_path, "w") as f:
                json.dump(data, f, indent=4)
            # messagebox.showinfo("Export Successful", f"Project exported to {file_path}")
        except Exception as e:
            messagebox.showerror("Export Failed", f"Failed to save project: {e}")

    def delete_gameobject(self, event):
        if self.current_level_index < 0:
            return

        # don't delete the grid
        if event.x % 32 == 0 or event.y % 32 == 0:
            return

        level_data = self.levels[self.current_level_index]
        canvas = level_data["canvas"]
        x, y = event.x, event.y
        items = canvas.find_overlapping(x, y, x, y)
        for item in items:
            canvas.delete(item)
            # Remove the item from the level data
            new_items = []
            for itm_name, x, y, img_id, _, _ in level_data["items"]:
                if img_id != item:
                    new_items.append((itm_name, x, y, img_id, 0, 0))
            level_data["items"] = new_items

    def execute_game(self):
        self.export()
        self.withdraw()

        # Get the directory where main.py is located
        current_dir = os.path.dirname(os.path.abspath(__file__))

        # Construct the path to the bin directory
        bin_dir = os.path.join(current_dir, "..", "Engine", "bin")

        makefile_dir = os.path.join(current_dir, "..", "Engine", "src")

        # Run make to build/update the game
        try:
            subprocess.run(["make"], check=True, cwd=makefile_dir)
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Build Failed", f"Make failed with error: {e}")
            self.deiconify()
            return
        except FileNotFoundError:
            messagebox.showerror("Not Found", "Make tool not found on this system.")
            self.deiconify()
            return

        # Construct the path to the game executable
        game_path = os.path.join(bin_dir, "game")

        # On Windows, you might need "game.exe" if the binary has that extension
        # If so:
        # game_path = os.path.join(bin_dir, "game.exe")

        # Check if the game file exists and is executable
        if not os.path.exists(game_path):
            messagebox.showerror(
                "Not Found", f"The game executable was not found at: {game_path}"
            )
            self.deiconify()
            return

        try:
            # Run the game, using bin_dir as the working directory
            subprocess.run(["./game"], check=True, cwd=bin_dir)
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Execution Failed", f"Failed to run the game: {e}")
        except FileNotFoundError:
            messagebox.showerror("Not Found", "The game executable was not found.")
        finally:
            # Show the GUI again once the executable finishes or if there's an error
            self.deiconify()

    def execute_demo(self):
        self.withdraw()

        # Get the directory where main.py is located
        current_dir = os.path.dirname(os.path.abspath(__file__))

        # Construct the path to the bin directory
        bin_dir = os.path.join(current_dir, "..", "Engine", "bin")

        makefile_dir = os.path.join(current_dir, "..", "Engine", "src")

        # Run make to build/update the game
        try:
            subprocess.run(["make"], check=True, cwd=makefile_dir)
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Build Failed", f"Make failed with error: {e}")
            self.deiconify()
            return
        except FileNotFoundError:
            messagebox.showerror("Not Found", "Make tool not found on this system.")
            self.deiconify()
            return

        # Construct the path to the game executable
        game_path = os.path.join(bin_dir, "game")

        # On Windows, you might need "game.exe" if the binary has that extension
        # If so:
        # game_path = os.path.join(bin_dir, "game.exe")

        # Check if the game file exists and is executable
        if not os.path.exists(game_path):
            messagebox.showerror(
                "Not Found", f"The game executable was not found at: {game_path}"
            )
            self.deiconify()
            return

        try:
            # Run the game, using bin_dir as the working directory
            subprocess.run(["./game", "demo"], check=True, cwd=bin_dir)
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Execution Failed", f"Failed to run the game: {e}")
        except FileNotFoundError:
            messagebox.showerror("Not Found", "The game executable was not found.")
        finally:
            # Show the GUI again once the executable finishes or if there's an error
            self.deiconify()


if __name__ == "__main__":
    app = LevelEditorApp()
    app.mainloop()
