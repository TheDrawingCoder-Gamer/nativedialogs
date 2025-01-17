/*
 * Copyright (c) 2006, Edwin van Rijkom, Nicolas Cannasse
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE HAXE PROJECT CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE HAXE PROJECT CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

package systools;

#if hl
import systools.hl.HLSystools;
#end
using Lambda;
typedef CompatString = #if hl HString #else String #end;
typedef CompatArray<T> = #if hl HArray<T> #else Array<T> #end;
typedef ArrayString = #if hl HArrayString #else Array<String>#end;
typedef FILEFILTERS = {
	var count: Int;
	var descriptions: Array<String>;
	var extensions: Array<String>;
}

class Dialogs {
	#if (cpp || neko)
	static var _message_box = systools.Loader.load("nativedialogs","dialogs_message_box",3);
	#end
	public static function message( title : String, msg : String, isError : Bool ) {
		#if hl
		HLSystools.messageBox(title,msg, isError);
		#elseif (cpp || neko)
		_message_box(title, msg, isError);
		#else 
		throw "Unsupported Platform";
		#end
	}
	#if (cpp || neko)
	static var _dialog_box = systools.Loader.load("nativedialogs","dialogs_dialog_box",3);
	#end
	public static function confirm( title : String, msg : String, isError : Bool ) : Bool {
		#if hl 
		return HLSystools.dialogBox(title, msg, isError);
		#elseif (cpp || neko)
		return _dialog_box(title, msg, isError);
		#else 
		throw "Unsupported Platform";
		return false;
		#end
	}
	#if (cpp || neko)
	static var _dialog_save_file = null;
	#end
	public static function saveFile( title : String, msg: String, initialDir : String,mask:FILEFILTERS=null) : String {
		#if (cpp || neko)
		if (_dialog_save_file == null)
		{
			try
			{
				_dialog_save_file = systools.Loader.load("nativedialogs","dialogs_save_file",4);
			}
			catch(e:Dynamic)
			{
				var savef = systools.Loader.load("nativedialogs","dialogs_save_file",3);
				_dialog_save_file = function(title,msg,initialDir,mask) return savef(title,msg,initialDir);
			}
		} 
		#elseif !hl
		throw "Unsupported Platform";
		return null;
		#end
		var cwd:String = Sys.getCwd();		//grab current working directory before it changes
		var str:String = #if hl HLSystools.saveFile(title, msg, initialDir, mask)#elseif (cpp || neko) _dialog_save_file(title, msg, initialDir,mask) #else null #end;
		Sys.setCwd(cwd);					//reset it afterwards
		return str;
	}
	#if (cpp || neko)
	static var _dialog_open_file = null;
	#end
	public static function openFile( title : String, msg : String, mask : FILEFILTERS, multi:Bool=true ) : Array<String> {
		#if (cpp || neko)
		if (_dialog_open_file == null)
		{
			try {
				_dialog_open_file = systools.Loader.load("nativedialogs","dialogs_open_file",4);
			}
			catch(e:Dynamic)
			{
				var openf = systools.Loader.load("nativedialogs","dialogs_open_file",3);
				_dialog_open_file = function(title,msg,mask,multi) return openf(title,msg,mask);
			}
		}
		#elseif !hl
		throw "Unsupported Platform";
		return null;
		#end

		var cwd:String = Sys.getCwd();		//grab current working directory before it changes
		var arr:Array<String> = #if hl HLSystools.openFile(title, msg, mask, multi) #elseif (cpp || neko) _dialog_open_file(title, msg, mask, multi) #else null #end;
		Sys.setCwd(cwd);					//reset it afterwards
		return arr;
	}
	#if (cpp || neko)
	static var _dialog_folder = systools.Loader.load("nativedialogs","dialogs_folder",2);
	#end
	public static function folder( title : String, msg: String ) : String {
		#if hl 
		return HLSystools.openFolder(title, msg);
		#elseif (cpp || neko)
		return _dialog_folder(title,msg);
		#else 
		throw "Unsupported Platform";
		return null;
		#end
	}
}
