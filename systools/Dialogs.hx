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
	var descriptions: CompatArray<String>;
	var extensions: CompatArray<String>;
}

class Dialogs {
	public static function message( title : String, msg : String, isError : Bool ) {
		Systools.messageBox(title, msg, isError);
	}
	public static function confirm( title : String, msg : String, isError : Bool ) : Bool {
		return Systools.dialogBox(title, msg, isError);
	}
	public static function saveFile( title : String, msg: String, initialDir : String,mask:FILEFILTERS=null) : String {
		var cwd:String = Sys.getCwd();		//grab current working directory before it changes
		var str:String = Systools.saveFile(title, msg, initialDir, mask);
		Sys.setCwd(cwd);					//reset it afterwards
		return str;
	}
	public static function openFile( title : String, msg : String, mask : FILEFILTERS, multi:Bool=true ) : Array<String> {

		var cwd:String = Sys.getCwd();		//grab current working directory before it changes
		var arr:Array<String> = Systools.openFile(title, msg, mask, multi);
		Sys.setCwd(cwd);					//reset it afterwards
		return arr;
	}
	public static function folder( title : String, msg: String ) : String {
		return Systools.openFolder(title, msg);
	}
}
