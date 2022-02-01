nativedialogs
========

fork of systools ( https://github.com/waneck/systools ) for Haxe 4


### Status ###
Most targets should be working. HashLink has not been tested, but Neko and CPP have not been _drastically_ changed. Dialogs are the only API supported.

### Neko usage with OpenFL ###
OpenFL will not include **nativedialogs.ndll** by default when building for the Neko or cpp platforms. To solve this you must include an additional line in your `project.xml` file, just after the `<haxelib name="nativedialogs" />` tag:
```xml
<ndll name="nativedialogs" haxelib="nativedialogs" />
```
