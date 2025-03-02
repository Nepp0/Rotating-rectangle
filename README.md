# Overview
The application renders a rotating rectangle by applying matrix transformations to its vertices, utilizing linear algebra principles. The rectangle does rotation around the *Y* and *Z* axes, with the rotation values determined by a **sine** function. This results in the rotation alternating between -1 and 1, causing the texture to infinitely flip and realign every *2π* time intervals.

Two textures are composited onto the rectangle, layered with distinct alpha (transparency) values. The alpha values are dynamically adjustable via input from the arrow keys, allowing for real-time adjustment of texture opacity.
