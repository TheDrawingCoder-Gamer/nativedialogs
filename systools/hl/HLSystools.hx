package systools.hl;

#if hl
import systools.Dialogs.FILEFILTERS;
abstract HString(hl.Bytes) from hl.Bytes to hl.Bytes {
    @:to 
    function toString():String {
        return cast @:privateAccess String.fromUTF8(this);
    }
    @:from
    static function fromString(str:String) {
        return cast @:privateAccess str.toUtf8();
    }
}
abstract ExtDynamic<T>(Dynamic) from T to T {}
@:hlNative("systools")
class HLSystools {
    public static function hlInit():Void {}
    public static function hlDialogsMessageBox(title:String, msg:String, error:Bool):Void {}
    public static function hlDialogsDialogBox(title:String, msg:String, error:Bool):Bool { return false; }
    public static function hlDialogsSaveFile(title:String, msg:String, initialdir:String, mask:ExtDynamic<FILEFILTERS>=null):HString {return null;}
    public static function hlDialogsOpenFile(title:String, msg:String, mask:ExtDynamic<FILEFILTERS>, multi:Bool):hl.NativeArray<HString> {return null;}
    public static function hlDialogsFolder(title:String, msg:String):HString { return null; }

    

}
#end