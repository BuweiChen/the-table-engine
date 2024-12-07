import engine

def main():
    # Create and run the game
    app = engine.GameApplication("Python Game Engine Test!")
    app.start()
    app.runLoop()

if __name__ == "__main__":
    main()