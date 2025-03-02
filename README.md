![ezgif com-optimize](https://github.com/user-attachments/assets/30ddff54-bee7-49c2-9db3-2cc49d9e70f9)
# Overview
The application renders a rotating rectangle by applying matrix transformations to its vertices utilizing linear algebra principles. The rectangle does rotation around the *Y* and *Z* axes, with the rotation values determined by a **sine** function. This results in the rotation alternating between -1 and 1, causing the texture to infinitely flip and realign every *2π* time intervals.

Two textures are composited onto the rectangle, layered with distinct alpha (transparency) values. The alpha values are dynamically adjustable via input from the arrow keys, allowing for real-time adjustment of texture opacity.

The colors in the application are dynamically modified by utilizing a **uniform** variable in the **fragment shader**. This uniform is used to pass a color value to each vertex, which is then interpolated across the rectangle's surface during rendering. The color values are updated over time by incorporating a time-based function which results in smooth transitions between different RGB values.
