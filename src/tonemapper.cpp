#include "tonemapper.h"

// Adapted from https://github.com/godotengine/godot/pull/52477/files,
// which is licensed under the MIT license.
Color3f Tonemapper::tonemapACESFitted(Color3f color, float exposure)
{
	const float A = 0.0245786f;
	const float B = 0.000090537f;
	const float C = 0.983729f;
	const float D = 0.432951f;
	const float E = 0.238081f;

  
	const Matrix3f odt_to_rgb(new float[9]{
      1.60475f, -0.53108f, -0.07367f,
      -0.10208f, 1.10813f, -0.00605f,
      -0.00327f, -0.07276f, 1.07602f
      });
  
  color *= exposure;
  Color3f color_tonemapped = (color * (color + Vector3f(A, A, A)) - Vector3f(B, B, B)) / (color * (color * C + Vector3f(D, D, D)) + Vector3f(E, E, E));
  color_tonemapped = odt_to_rgb * color_tonemapped;

  Color3f white = Color3f(1.0f, 1.0f, 1.0f);
  white *= exposure;

  Color3f white_tonemapped = (white * (white + Vector3f(A, A, A)) - Vector3f(B, B, B)) / (white * (white * C + Vector3f(D, D, D)) + Vector3f(E, E, E));

  return Vector3f::clamp(color_tonemapped / white_tonemapped, 0.0f, 1.0f);
}
