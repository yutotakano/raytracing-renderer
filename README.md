# Ray-Tracing Renderer Project

This is a C++ implementation of a ray-tracer, which was my project for the University of Edinburgh 2023-24 Computer Graphics: Rendering course. 

It features:
- Three different tracers:
  - Binary intersection tracer;
  - Blinn-Phong ray-tracer with reflection and refraction;
  - Path-tracer using russian roulette-based Multiple Importance Sampling (sample BSDF, sample light, combine with weights)
- Scenes and rendering:
  - Recursive JSON scene description parser, using the object-oriented structure of the code;
  - Cylinder, sphere, triangles and mesh (OBJ file) shapes
  - UV-mapped texture including OBJ, using texture coordinates parsed and interpolated in barycentric coordinates
  - Area light, point light, sunlight
- Two different cameras:
  - Basic pinhole camera
  - Physically-accurate lens camera (supports sampling to simulate aperture)
- Extras:
  - BVH implementation for fast intersection checks
  - Linear and [ACES-Fitted](https://github.com/godotengine/godot/pull/52477/files) tone-map implementations
  - OpenMP parallelised rendering;
  - SDL2 UI to show in-progress and completed renders

Prerequisites for setup:
- Makefile supports compilation only on an Apple Silicon-based Mac (Homebrew has to be installed at `/opt/homebrew`)
- `lSDL2` has to be in `/opt/homebrew/lib`, headers in `/opt/homebrew/include`
- `libomp` has to be in `/opt/homebrew/opt/libomp/lib`, headers in `/opt/homebrew/opt/libomp/include`

Build:
```bash
$ make best
```

Run:
```bash
$ ./main [scene_json_file]
```

Optional arguments:
```
--no-preview                    Disables the SDL preview window.
--output <filename>             Filename to write the PPM image to.
--tonemap <aces_fitted|linear>  Tonemap algorithm to use.
```

---

> [!NOTE]  
> This project was implemented for the UoE Computer Graphics: Rendering 2023-24 course, and as such the repository is not maintained on an active basis.
