package systools.hl;

#if hl
import systools.Dialogs.FILEFILTERS;
import hl.Bytes as HLBytes;
import hl.NativeArray;
using Lambda;
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
@:forward
abstract HArray<T>(hl.NativeArray<T>) from hl.NativeArray<T> to hl.NativeArray<T> {
    @:from 
    static function fromArray<T>(arr:Array<T>):HArray<T> {
        return @:privateAccess untyped arr.array();
    }
    @:to
    function toArray():Array<T> {
        return [for (i in hl.types.ArrayObj.alloc(this)) i];
    }
}
abstract ExtDynamic<T>(Dynamic) from T to T {}
@:hlNative("systools")
class HLSystools {
    public static function hlInit():Void {}
    public static function hlDialogsMessageBox(title:String, msg:String, error:Bool):Void {}
    public static function hlDialogsDialogBox(title:String, msg:String, error:Bool):Bool { return false; }
    public static function hlDialogsSaveFile(title:String, msg:String, initialdir:String, mask:ExtDynamic<FILEFILTERS>=null):HString {return null;}
    public static function hlDialogsOpenFile(title:String, msg:String, mask:ExtDynamic<FILEFILTERS>, multi:Bool):HArray<HString> {return null;}
    public static function hlDialogsFolder(title:String, msg:String):HString { return null; }

    

}
#end