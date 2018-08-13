# HOW TO Write a scene file
A scene is represented by a JSON-formatted file.

#### What is JSON ?
[JavaScript Object Notation](https://www.json.org) (or just JSON) is a file format consisting of many attribute-value pairs ([Wiki](https://en.wikipedia.org/wiki/JSON)).
This format is popular for its legibility.

A JSON file describe one object, which contain one or more combination of an attribute and a value (which is called a pair). A pair is formatted as the following :
> attribute: value,

---
An attribute must be a string. A value can be:

* a floating point number,
* an integer number,
* a boolean,
* a string (represented by ""),
* an array of pairs (represented by []),
* an object (represented by {}).

Each pairs in an object or an array must be separated by a coma.

### How the scene is formatted ?
_Note: Each 3-dimensionnal point, direction vector or rotation vector is represented by an array of 3 float numbers._
_For colors, you should use an array of 3 float numbers between 0 and 255, representing de RGB color._
_If an attribute have a default value, it can be omitted in the scene file._

#### A scene file must contain :
* a "background_color" attribute. By default, it is set to [0, 0, 0].
* a "depth" attribute, representing the number of possible bouncing of the primary rays. It is represented by an unsigned integer.

* **a "camera" object, which must contain :**
    * a "pos" attribute, describing the position of the object.
    * an "angle" rotation vector. By default, the camera looks toward [0, 0, -1]. The rotation is specified in degree.
    * an aperture angle named "fov" (for Field of Vision). by default, it is set to 90.

* **a "lights" array of objects describing the light sources in the scene. Each object in the array must contain**:
    * a position named "pos".
    * a "color" attribute. By default, it is set to [255, 255, 255].
    * a "power" number, between 0 and 5. By default, it is set to one.

* **an "objects" array of objects. Each object represent an object in the scene (sphere, cylinder, ...) and must have:**
 * a "type" string, which define what type of object it is. The different possible types are :
    * sphere,
    * cone,
    * cylinder,
    * plane,
    * disk,
    * triangle,
    * paraboloid,
    * mesh.
 * a "pos" attribute.
 * an "angle" rotation vector for the direction of the object. By default, it is set to [0, 1, 0].
 * a "color" attribute. By default, it is set to [255, 255, 255].
 * a "material" object, describing some properties of the object (see the Material section).
 * any special information, depending on the type of the object (see the Specifics Object Types Attributes section).
---
### The Special Object Types Attributes:
Each object might take one or many informations that depend of their type. Here is the list, sorted by type:

* **Sphere, Disk:**
    * a "radius" attribute, defined by a float value.
* **Cone:**
    * an "opening_angle" attribute, defined by a float value between 0 and 90 excluded,
    * a "simple" attribute, defined by a boolean, specifying if the cone is simple or double (set by default to double),
    * a "length" attribute, defined by a float value. By default, the cone is infinite).
* **Cylinder:**
    * a "radius" attribute, defined by a float value.
    * a "length" attribute, defined by a float value. By default, the cone is infinite.
* **Plane:** There is no special attribute for the plane.
* **Paraboloid:**
    * a "length" attribute, defined by a float value.
* **Mesh:** See The Meshes section for more information.
---
### The Material:
Material is a (JSON) object, which describe the property of a corresponding object.
Here is the possible attributes in the material attribute:

* a "property" string, which state the property of the object. It can be:
    * reflective (mirror),
    * refractive (transparent),
    * negative (any colision with a negative object is erased),
    * portal (see the Portal section),
    * none (the default plain object).
* a "coefficient" float value (between 0 and 1), describing how much the object is non-plain. By default, it is set to 0.
* a "refractive_index" float value, describing how the ray are refracted inside the object (you can seek for informations about it on internet).
* a "perturbation" (JSON) object, defining a color/normal change, or a texture to apply. This object must contain the following attributes:
    * "frequence": float value,
	* "depth": integer value,
	* "seed": integer value,
	* "type": string specifying the desired perturbation ("wood", "water", "perlin", "sin_marble", "line_marble").

* a "output_pos" position (reserved for portals).

---
### The Meshes:

A Mesh is a collection of vertices, edges and faces that describe the shape of a 3D object. To be more precise:
 * a **vertex** is a single point,
 * an **edge** is a segment connecting 2 vertices.
 * a **face** is a flat surface enclosed by edges (it can also be called "polygons").

In a YARP scene file, in order to describe a mesh, you do not need to define any edge. All you need to do is define an object with the "mesh" type, and add the following special attribute:
 * a "vertices" attribute, defined by one array of several arrays composed of 3D point.
 * a "faces" attribute, defined by one array of several arrays composed of 3 or more integer values. These values are indices of the vertices array.

---
### The Portals:

Portals are a Unique YARP-implemented property of an object. Any primary ray touching a portal object will be teleported to the output_pos position.
The teleported rays keep the same direction threw the portal.

---
### YARP Pro Tips:
* Set the fov to 45 to avoid distortion.
* If you want to see a transparent non-flat object, you should set the depth to a value >= 2, or the ray might stop inside the object.
* Teleporting a ray with a portal object count as a bounce. You should adapt the depth of the scene accordingly.
* A good way to avoid infinite bouncing of the rays is to slightly reduce the coefficient of the properties by a few percentages.
* Dont forget your physics course! A full red (255, 0, 0) object can't be enlightened by a full blue (0, 0, 255) light.
