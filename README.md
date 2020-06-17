
# C++ レイトレーサー

<p align="center">
  <img width="175" height="175" src=https://user-images.githubusercontent.com/66903979/84857372-e1a3fd00-b0a3-11ea-8695-81bb09b6c616.jpg">
</p>

このレイトレーサーは、ホイットレイレイトレーシングアルゴリズム*のC ++実装です。

このプロジェクトの目標は、1979年にターナーホイットによって提案された再帰レイトレーサーを完全にサポートする3D APIを提供することです。

目標を達成するために、3D APIはオブジェクト指向のアプローチで設計されています。 これは、ベクトルおよび行列代数をサポートするクラスを実装します。

## どのように機能しますか？

最終的な画像の各ピクセルの色は、次のように計算されます。

1- 光線がシーンにキャストされ、サーフェスが「ヒット」するポイントが特定されます。

2- #1を照らすライトを決定するために、ポイント＃1からシーン内のすべての光源に向かって光線が投影されます。

3- #1が反射面の場合、反射方向に光線を投じ、そこで反射される色を再帰的に決定します。

4- #1が透明なサーフェスの場合、屈折の方向からプロセスを開始します。

5- #1に寄与するすべての色値（表面色、反射、屈折）を追加し、結果をピクセルの最終色として返します。

このレイトレーサーの開発は、Jamis Buckレイトレーサーチャレンジの仕事にも影響を受けています。**

# C++ Ray Tracer 
This Ray Tracer is a C++ implementation of the Whitted ray tracing algorithm*.

The goal of this project is to provide a 3D API that fully supports a recursive ray tracer as proposed by Turner Whitted in 1979.

To accomplish the goal, a 3D API is designed with an object oriented approach. It implements classes that support Vector and Matrix algebra.

## How does it work?
The color of each pixel of the final image is calculated as follows:

1- A ray is casted into the scene, and the point where a surface is "hitted" is identified.

2- A ray is casted from point #1 toward every light source in the scene, in order to determine the lights that illuminate it.

3- If #1 is a reflective surface, cast a ray in the reflection direction, and determine the color that is reflected there, recursively.

4- If #1 is a transparent surface, start the process in the direction of refraction.

5- Add all color values that contribute to #1 (surface color, reflection, refraction) and return the result as the final color of the pixel.

The development of this ray tracer is also inspired by Jamis Buck Ray Tracer Challenge work.**
 
 
 
 
 
 

**Turner Whitted. 1980. An improved illumination model for shaded display. Commun. ACM 23, 6 (June 1980), 343–349.*

***Buck, Jamis. Ray tracer challenge. Raleigh : The Pragmatic Bookshelf, 2018*
