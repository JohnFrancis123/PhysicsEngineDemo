# Physics Engine Demo

A 2D physics engine demonstration built in C++ using SDL2, OpenGL, and GLM. This project showcases a custom game engine with particle systems, rigid body dynamics, collision detection, and character animation.

## Features

### Physics System
- **Rigid Body Dynamics** - Real-time physics simulation with mass, velocity, and acceleration
- **Particle System** - Dynamic particle effects with customizable lifetimes and behaviors
- **Collision Detection** - Accurate collision handling between rigid bodies
- **Environmental Forces**
  - Gravity simulation
  - Buoyancy effects
  - Wind forces
  - Random force application

### Graphics & Animation
- **Sprite Animation System** - Frame-based animation with sprite sheets
- **2D Rendering** - Hardware-accelerated rendering with SDL2 and OpenGL
- **Texture Support** - TGA image format loading
- **Custom Rendering Pipeline** - Efficient draw calls and blend modes

### Game Systems
- **State Machine** - Character state management (Idle, Jump, Crouch)
- **Input Controller** - Keyboard and mouse input handling
- **Resource Management** - Custom asset loading and memory management
- **Object Pooling** - Efficient memory reuse for particles and sprites
- **Stack Allocator** - Custom memory allocator for performance optimization

## Tech Stack

- **Language**: C++ 
- **Graphics**: SDL2, OpenGL, GLEW
- **Math**: GLM (OpenGL Mathematics)
- **Audio**: SDL2_mixer
- **Fonts**: SDL2_ttf
- **Window Management**: GLFW

## Prerequisites

- **Windows OS** (configured for Visual Studio)
- **Visual Studio 2017 or later** with C++ development tools
- **Git** for cloning the repository

All dependencies (SDL2, OpenGL libraries, etc.) are included in the `External/` directory.

## Installation & Setup

### 1. Clone the Repository
```bash
git clone https://github.com/JohnFrancis123/PhysicsEngineDemo.git
cd PhysicsEngineDemo
```

### 2. Open the Solution
- Open `GameEngineWeek12.sln` in Visual Studio
- The solution includes all necessary project configurations

### 3. Build the Project
- Select your build configuration (Debug/Release)
- Build the solution: `Build > Build Solution` or press `Ctrl+Shift+B`
- All external dependencies are pre-configured and will link automatically

### 4. Run the Demo
- Press `F5` to run with debugging, or `Ctrl+F5` to run without debugging
- The application window will launch and display the physics simulation

## Controls

- **ESC** - Exit the application
- **Arrow Keys/WASD** - Character movement (if implemented)
- **Space** - Character jump/interaction

## Project Structure

```
PhysicsEngineDemo/
├── Assets/                    # Game assets
│   ├── Textures/             # Sprite sheets and textures (.tga files)
│   ├── Fonts/                # TrueType fonts
│   └── Audio/                # Sound effects and music
├── External/                  # Third-party libraries
│   ├── SDL2-2.26.1/          # SDL2 core library
│   ├── SDL2_mixer-2.6.2/     # Audio mixing library
│   ├── SDL2_ttf-2.20.0/      # Font rendering library
│   ├── glew-2.2.0/           # OpenGL Extension Wrangler
│   ├── glfw-3.4/             # Window and context management
│   └── glm/                  # OpenGL Mathematics library
├── GameEngineWeek12/          # Main source code
│   ├── GameController.cpp/h   # Main game loop and initialization
│   ├── PhysicsController.cpp/h # Physics simulation engine
│   ├── RigidBody.cpp/h        # Rigid body implementation
│   ├── Particle.cpp/h         # Particle system
│   ├── Renderer.cpp/h         # Rendering system
│   ├── InputController.cpp/h  # Input handling
│   ├── Heroine.cpp/h          # Character implementation
│   ├── HeroineState.cpp/h     # Character state machine
│   ├── SpriteSheet.cpp/h      # Sprite management
│   ├── ObjectPool.h           # Object pooling pattern
│   ├── StackAllocator.cpp/h   # Custom memory allocator
│   └── ...                    # Additional engine systems
└── GameEngineWeek12.sln       # Visual Studio solution file
```

## Key Components

### Physics Controller
Manages all physics objects and applies forces:
- Gravity
- Collision resolution
- Force accumulation and integration

### Rigid Body
Base class for physics objects with properties:
- Position, velocity, acceleration
- Mass and forces
- Buoyancy and environmental effects

### Particle System
Extends RigidBody with:
- Lifetime management
- Size interpolation
- Object pooling for performance

### Character System (Heroine)
Demonstrates physics integration with:
- State machine pattern
- Animated sprites
- Physics-based movement

## Assets Included

- **Warrior.tga** - Animated character sprite sheet (17x6 frames)
- **Circle.tga** - Particle texture
- **Fire.tga** - Fire effect sprite sheet
- **Smoke.tga** - Smoke particle sprite sheet
- **Rock.tga** - Rock/debris sprites

## Design Patterns Used

- **Singleton Pattern** - GameController, PhysicsController, Renderer
- **State Pattern** - Character state management
- **Object Pool Pattern** - Efficient particle and sprite reuse
- **Factory Pattern** - Asset creation and management
- **Observer Pattern** - Input event handling

## Development

### Adding New Physics Objects
```cpp
// Add a new rigid body
RigidBody* body = PhysicsController::Instance().AddRigidBody(
    glm::vec2(x, y),      // Position
    glm::vec2(vx, vy),    // Initial velocity
    mass                   // Mass
);

// Add a new particle
Particle* particle = PhysicsController::Instance().AddParticle(
    glm::vec2(x, y),      // Position
    lifetime               // Lifetime in seconds
);
```

### Custom Forces
```cpp
// Set environmental forces on a rigid body
body->SetBuoyancy(glm::vec2(0.0f, -9.8f));
body->SetWind(glm::vec2(5.0f, 0.0f));
body->SetRandomForce(glm::vec2(1.0f, 1.0f));
```

## Known Issues

- Currently configured for Windows/Visual Studio only
- Asset paths are relative and require running from specific directories
- Some physics parameters may need tuning for specific scenarios

## Contributing

This is an educational/demonstration project. Feel free to fork and experiment with:
- Additional physics features (springs, joints, constraints)
- More particle effects
- Enhanced collision detection (SAT, GJK)
- Cross-platform support (Linux, macOS)

## License

This project is available for educational purposes. Check individual library licenses in the `External/` directory.

## Acknowledgments

- SDL2 development team for the multimedia library
- OpenGL community for graphics support
- GLM for math operations
- Various sprite artists for asset contributions

## Contact

For questions or feedback, please open an issue on the GitHub repository.

---

**Built with as a physics engine demonstration project**
