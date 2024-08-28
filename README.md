# CPU Graphic Engine

Welcome to the CPU Graphic Renderer repository! This project is an exploration of computer graphics rendering using only the CPU. Made for the discipline of Computer Graphics in the 3rd year of study.

## Features

- 3D geometry rendering
- Texture mapping and lighting effects
- Transformations such as rotation, scaling, and translation
- Lambert lighting system
- Phong lighting system
- Physically Based Rendering

## Tasks Completed

According to the tasks assigned to me, the following features have been implemented and are in use:

### Geometry and Transformations

- Developed a parser for .obj files
- Implemented matrix transformations for coordinates from model space to world space
- Implemented matrix transformations for coordinates from world space to view space
- Implemented matrix transformations for coordinates from view space to projection space
- Implemented matrix transformations for coordinates from projection space to screen space
- Implemented wireframe rendering of 3D models
- Implemented a triangle rasterization algorithm
- Implemented back-face culling and hidden surface removal for 3D objects

### Lighting and Shading

- Implemented flat shading and the Lambert lighting model
- Implemented the Phong shading model
- Implemented the Phong lighting model
- Implemented an algorithm for applying diffuse maps
- Implemented an algorithm for applying normal maps
- Implemented an algorithm for applying specular maps
- Implemented an algorithm for interpolating vertex attributes with perspective correction

## Installation
Configuration of the cmake project will be done later. At the moment it is a project in visual studio.

## Usage

The CPU Graphic Engine provides a simple interface for rendering 3D scenes. You can specify the geometry, textures, lighting, and camera parameters using keybindings.

Example usage:


### 1. Wavefront model (Press 1)

<img src="https://github.com/IntensioT/CPU_Graphic_Renderer/assets/90414976/5a01724a-401e-4cd2-a212-7685e70f17e4" width="600" height="500" alt="My Image">

### 2. Wavefront with normals (Press 2)

<img src="https://github.com/IntensioT/CPU_Graphic_Renderer/assets/90414976/31d71cee-423f-4162-b604-05a8ccce4e1e" width="600" height="500" alt="My Image">

### 3. Lambert light and scanline rasterization (Press 3)

<img src="https://github.com/IntensioT/CPU_Graphic_Renderer/assets/90414976/6f70a67e-111b-4009-8025-f159bb01aa6e" width="600" height="500" alt="My Image">

### 4. Phong light and barycentric rasterization (Press 4)

<img src="https://github.com/IntensioT/CPU_Graphic_Renderer/assets/90414976/f4494a0e-082b-4e49-a0ea-42998a25ff6e" width="500" height="500" alt="My Image">

### 5. Simple texturing (Press 5)

<img src="https://github.com/IntensioT/CPU_Graphic_Renderer/assets/90414976/8f8e469d-6411-4f51-a098-8b727db7ed0d" width="500" height="500" alt="My Image">

### 6. Texturing with phong light (Press 6)

<img src="https://github.com/IntensioT/CPU_Graphic_Renderer/assets/90414976/3efc393a-51b3-4949-b145-4e39eea910a2" width="600" height="500" alt="My Image">

### 7. Texturing with phong light and billinear filtration (Press 7)

![image](https://github.com/IntensioT/CPU_Graphic_Renderer/assets/90414976/f1df324d-1722-4daa-8ec6-49e820ee5fdb)

### 8. Normal map and specular added (Press 8)

![image](https://github.com/IntensioT/CPU_Graphic_Renderer/assets/90414976/3fe69c08-232b-4b4e-9533-04728f01eb7c)

### 9. PBR light model with different materials and other params (Press 9)

<img src="https://github.com/IntensioT/CPU_Graphic_Renderer/assets/90414976/e0853431-7746-4d7e-bf81-47fd1e0180a3" width="580" height="500" alt="My Image">

### 10. PBR light with texturing and mrao map (Press 10)

![image](https://github.com/IntensioT/CPU_Graphic_Renderer/assets/90414976/1f7e389b-3e7e-40a5-b890-7737bef1b3f6)


