package systools.hl;

#if hl
import systools.Dialogs.FILEFILTERS;
import hl.Bytes as HLBytes;
import hl.NativeArray;
import hl.BytesAccess;
import hl.UI8;
import Lambda;


abstract HString(hl.Bytes) from hl.Bytes to hl.Bytes {
    @:to 
    public function toString():String {
        if (this == null)
            return "";
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
        return cast (untyped arr.array : hl.NativeArray<T>);
    }
    public function iterator() {
        return new hl.types.ArrayObj.ArrayObjIterator<T>(hl.types.ArrayObj.alloc(this));
    }
}
@:forward 
abstract HArrayString(hl.NativeArray<hl.Bytes>) from hl.NativeArray<hl.Bytes> to hl.NativeArray<hl.Bytes> {
    @:from 
    public static function fromArray(arr:Array<String>):HArrayString {
        var goodArr = [for (i in arr) @:privateAccess i.toUtf8()];
        return cast (untyped goodArr.array : hl.NativeArray<hl.Bytes>);
    }
    @:to 
    public function toArray():Array<String> {  
        
        var goodArr:Array<String> = [];
        for (i in new hl.NativeArrayIterator(this)) {
            var bytes:hl.Bytes = i ;
            goodArr.push(@:privateAccess String.fromUTF8(bytes));
        }
        
        return goodArr;
    }
}

typedef HLFileFilters = {
    var count:Int;
    var descriptions:NativeArray<hl.Bytes>;
    var extensions:NativeArray<hl.Bytes>;
};
abstract AbstFileFilters(HLFileFilters) from HLFileFilters to HLFileFilters {
    @:from 
    public static function fromFILEFILTERS(filters:FILEFILTERS) {
        if (filters == null)
            return null;
        var good:HLFileFilters = {count: 0, descriptions: null, extensions: null};
        good.count = filters.count;
        good.descriptions = new NativeArray<hl.Bytes>(filters.count);
        good.extensions = new NativeArray<hl.Bytes>(filters.count);
        for (i in 0...filters.count) {
            good.descriptions[i] = @:privateAccess filters.descriptions[i].bytes;
            good.extensions[i] = @:privateAccess filters.extensions[i].bytes;
        }
        return cast good;
    }
}
abstract ExtDynamic<T>(Dynamic) from T to T {}
@:hlNative("nativedialogs")
class CLib {
    public static function hlInit():Void {}
    public static function hlDialogsMessageBox(title:String, msg:String, error:Bool):Void {}
    public static function hlDialogsDialogBox(title:String, msg:String, error:Bool):Bool { return false; }
    public static function hlDialogsSaveFile(title:String, msg:String, initialdir:String, mask:ExtDynamic<HLFileFilters>=null):HString {return null;}
    public static function hlDialogsOpenFile(title:String, msg:String, mask:ExtDynamic<HLFileFilters>, multi:Bool):HArrayString {return null;}
    public static function hlDialogsFolder(title:String, msg:String):HString { return null; }

    

}
class HLSystools {
    static var initialized = init();
    public static function init() {
        if (initialized)
            return true;
        initialized = true;
        CLib.hlInit();
        return true;
    }
    public static function messageBox(title:String, msg:String, error:Bool) {
        if (!initialized) 
            init();
        CLib.hlDialogsMessageBox(title, msg, error);
    }
    public static function dialogBox(title:String, msg:String, error:Bool):Bool {
        if (!initialized) 
            init();
        return CLib.hlDialogsDialogBox(title, msg, error);
    }
    public static function saveFile(title:String, msg:String, initialdir:String, mask:FILEFILTERS=null):String {
        if (!initialized) 
            init();
        var thingie:HString = CLib.hlDialogsSaveFile(title, msg, initialdir,  cast AbstFileFilters.fromFILEFILTERS(mask)).toString();
        if (thingie == null)
            return null;
        return thingie.toString();
    }
    public static function openFile(title:String, msg:String, mask:Null<FILEFILTERS>, multi:Bool):Array<String> {
        if (!initialized) 
            init();
        var thingie:HArrayString = CLib.hlDialogsOpenFile(title, msg, cast AbstFileFilters.fromFILEFILTERS(mask), multi);
        if (thingie == null)
            return null;
        return thingie.toArray();
    }
    public static function openFolder(title:String, msg:String):HString { 
        if (!initialized) 
            init();
        return cast CLib.hlDialogsFolder(title, msg);
    }
}
#end
