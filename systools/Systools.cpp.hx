package systools;

#if cpp 
import cpp.ConstCharStar;
import cpp.RawConstPointer;
import cpp.RawPointer;
import cpp.Pointer;
import cpp.Char;
import systools.Dialogs;
@:buildXml("<include name='${haxelib:systools}/project/build.xml'/>")
@:include("apicpp.hpp")
extern class CPPLib {
    @:native("systools_init") public static function init():Void;
    @:native("dialogs_message_box") public static function messageBox(title:String, msg:String, error:Bool):Void;
    @:native("dialogs_dialog_box") public static function dialogBox(title:String, msg:String, error:Bool):Bool;
    @:native("dialogs_save_file") public static function saveFile(title:String, msg:String, initialDir:String, mask:CFileFilters):String;
    @:native("dialogs_open_file") public static function openFile(title:String, msg:String, mask:CFileFilters, multi:Bool):Array<String>;
    @:native("dialogs_folder") public static function openFolder(title:String, msg:String):String;
    @:native("new_filefilters") public static function newFileFilters(count:Int, descriptions:Array<String>, extensions:Array<String>):CFileFilters;
}

@:unreflective
@:structAccess
@:native("::cpp::Reference<ARGS_FILEFILTERS>")
@:include("api.h")
extern class CFileFilters {
    var count:cpp.Int64;
    var descriptions:cpp.RawPointer<RawConstPointer<Char>>;
    var extensions:cpp.RawPointer<RawConstPointer<Char>>;

}
class Systools {
    static var initialized = init();
    private static function init() {
        if (initialized)
            return true;
        initialized = true;
        CPPLib.init();
        return true;
    }
    private static function newFileFilters(filters:FILEFILTERS) {
        return CPPLib.newFileFilters(filters.count, filters.descriptions, filters.extensions);
    }
    public static function messageBox(title:String, msg:String, error:Bool):Void {
        init();
        CPPLib.messageBox(title, msg, error);
    }
    public static function dialogBox(title:String, msg:String, error:Bool):Bool {
        init();
        return CPPLib.dialogBox(title, msg, error);
    }
    public static function saveFile(title:String, msg:String, initialDir:String, mask:FILEFILTERS=null):String {
        init();
        return CPPLib.saveFile(title, msg, initialDir, newFileFilters(mask));

    }

    public static function openFile(title:String, msg:String, mask:Null<FILEFILTERS>, multi:Bool):Array<String> {
        init();
        return CPPLib.openFile(title, msg, newFileFilters(mask), multi);
    }
    public static function openFolder(title:String, msg:String):String {
        init();
        return CPPLib.openFolder(title, msg);
    }
}
#end
