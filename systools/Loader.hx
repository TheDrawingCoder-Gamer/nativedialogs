package systools;
#if neko

import neko.Lib;
class Loader
{
	private static var init = false;

	public static function load(lib:String, s:String, n:Int):Dynamic
	{

		if (!init)
		{
			loadNekoAPI();
			Lib.load("systools","systools_init",0)();
			init = true;
		}

		return Lib.load(lib,s,n);
	}

	public static function loadNekoAPI()
	{
		var i = Lib.load("systools","neko_init", 5);
		if (i != null)
		{
			i(function(s) return new String(s), function(len:Int) { var r = []; if (len > 0) r[len - 1] = null; return r; }, null, true, false);
		}
	}
}
#end