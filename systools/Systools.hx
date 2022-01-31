package systools;

import systools.Dialogs.FILEFILTERS;

class Systools {
    private static function init():Void {
        throw "Not Implemented";
    }
    public static function messageBox(title:String, msg:String, error:Bool) {
        throw "Not Implemented";
    }
    public static function dialogBox(title:String, msg:String, error:Bool):Bool {
        throw "Not Implemented";
        return false;
    }
    public static function saveFile(title:String, msg:String, initialDir:String, ?mask:FILEFILTERS):String {
        throw "Not Implemented";
        return null;
    }
    public static function openFile(title:String, msg:String, mask:Null<FILEFILTERS>, multi:Bool):Array<String> {
        throw "Not Implemented";
        return null;
    }
    public static function openFolder(title:String, msg:String):String {
        throw "Not Implemented";
        return null;
    }
}