package systools;

class Systools {
    static var _message_box:(String, String, Bool)->Void = systools.Loader.load("systools", "dialogs_message_box", 3);
    public static function messageBox(title:String,msg:String, error:Bool):Void {
        _message_box(title, msg, error);
    }
    static var _dialog_box:(String, String, Bool)->Bool = systools.Loader.load("systools", "dialogs_dialog_box", 3);
    public static function dialogBox(title:String, msg:String, error:Bool):Bool {
        _dialog_box(title, msg, error);
    }
    static var _dialog_save_file = null;
    public static function saveFile(title:String, msg:String, initialDir:String, mask:FILEFILTERS = null):String {
        if (_dialog_save_file == null) {
            try
            {
                _dialog_save_file = systools.Loader.load("systools", "dialogs_save_file", 4);
            } catch (e:Dynamic) {
                var savef = systools.Loader.load("systools", "dialogs_save_file", 3);
                _dialog_save_file = function(title,msg,initialDir,mask) return savef(title, msg, initialDir);
            }
        }
        return _dialog_save_file(title, msg, initialDir, mask);
    }

    static var _dialog_open_file = null;
    public static function openFile(title:String, msg:String, mask:FILEFILTERS, multi:Bool):Array<String> {
        if (_dialog_open_file == null) {
            try
            {
                _dialog_open_file = systools.Loader.load("systools", "dialogs_open_file", 4);
            } catch (e:Dynamic) {
                var openf = systools.Loader.load("systools", "dialogs_open_file", 3);
                _dialog_open_file = function(title,msg,mask,multi) return openf(title, msg, mask);
            }
        }
        return _dialog_open_file(title, msg, mask, multi);
    }
    static var _dialog_folder = systools.Loader.load("systools", "dialogs_folder", 2);
    public static function openFolder(title:String, msg:String) {
        return _dialog_folder(title, msg);
    }
}