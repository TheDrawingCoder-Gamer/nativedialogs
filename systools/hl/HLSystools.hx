package systools.hl;

#if hl
import systools.Dialogs.FILEFILTERS;
abstract HString(String) from String to String {
    @:from 
    static function fromBytes(bytes:hl.Bytes) {
        return cast @:privateAccess String.fromUTF8(bytes);
    }
    @:to 
    function toBytes():hl.Bytes {
        return @:privateAccess this.toUtf8();
    }
}
@:hlNative("systools")
class HLSystools {
    public static function hlInit():Void {}
    public static function hlDialogsMessageBox(title:String, msg:String, error:Bool = false):Void {}
    public static function hlDialogsDialogBox(title:String, msg:String, error:Bool = false):Bool { return false; }
    public static function hlDialogsSaveFile(title:String, msg:String, initialdir:String, mask:FILEFILTERS=null):HString {return null;}
    public static function hlDialogsOpenFile(title:String, msg:String, mask:FILEFILTERS, multi:Bool):Array<HString> {return null;}
    public static function hlDialogsFolder(title:String, msg:String):HString { return null; }
    public static function hlClipboardSetText(text:String):Int { return 0; }
    public static function hlClipboardGetText():HString {return null; }
    public static function hlClipboardClear():Void {}
    public static function hlMiscGetKeyState(key:Int):Int {return 0; }
    public static function hlBrowserLaunch(url:String):Bool {return false; }
    public static function hlFileutilsGetTempFolder():HString {return null; }
    public static function hlDisplayGetScreenSize():{h:Int, s:Int} { return null;}
    public static function hlRegistrySetValue(key:Int, subkey:String, valuename:String, v:String):Void { }
    public static function hlRegistryGetValue(key:Int, subkey:String, valuename:String):HString {return null;}
    public static function hlRegistryDeleteKey(key:Int, subkey:String):Void {}
    

}
#end