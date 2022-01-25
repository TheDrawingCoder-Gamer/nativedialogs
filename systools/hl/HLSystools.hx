package systools.hl;

#if hl

typedef FILEFILTERS = {
	var count: Int;
	var descriptions: Array<String>;
	var extensions: Array<String>;
}
abstract HString(String) from String to String {
    @:from 
    static function fromBytes(bytes:hl.Bytes) {
        return cast bytes.toBytes().toString();
    }
    @:to 
    function toBytes():hl.Bytes {
        return hl.Bytes.fromBytes(haxe.io.Bytes.ofString(this));
    }
}
@:hlNative("systools")
class HLSystools {
    public static function hlInit():Void {}
    public static function hlDialogsMessageBox(title:String, msg:String, error:Bool = false):Void {}
    public static function hlDialogsDialogBox(title:String, msg:String, error:Bool = false):Bool { return null; }
    public static function hlDialogsSaveFile(title:String, msg:String, initialdir:String, mask:FILEFILTERS=null):HString {return null;}
    public static function hlDialogsOpenFile(title:String, msg:String, mask:FILEFILTERS, multi:Bool):Array<HString> {return null;}
    public static function hlDialogsFolder(title:String, msg:String):HString { return null; }
    public static function hlClipboardSetText(text:String):Int { return null; }
    public static function hlClipboardGetText():HString {return null; }
    public static function hlClipboardClear():Void {}
    public static function hlMiscGetKeyState(key:Int):Int {return null; }
    public static function hlBrowserLaunch(url:String):Bool {return null; }
    public static function hlFileutilsGetTempFolder():HString {return null; }
    public static function hlDisplayGetScreenSize():{h:Int, s:Int} { return null;}
    public static function hlRegistrySetValue(key:Int, subkey:String, valuename:String, v:String):Void { }
    public static function hlRegistryGetValue(key:Int, subkey:String, valuename:String):HString {return null;}
    public static function hlRegistryDeleteKey(key:Int, subkey:String):Void {}
    

}
#end