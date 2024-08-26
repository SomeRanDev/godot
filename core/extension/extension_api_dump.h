/**************************************************************************/
/*  extension_api_dump.h                                                  */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef EXTENSION_API_DUMP_H
#define EXTENSION_API_DUMP_H

#include "core/extension/gdextension.h"

#ifdef TOOLS_ENABLED

class GDExtensionAPIDump {
public:
	static Dictionary generate_extension_api(bool p_include_docs = false);
	static void generate_extension_json_file(const String &p_path, bool p_include_docs = false);
	static Error validate_extension_json_file(const String &p_path);
};

class GDExtensionAPIType {
public:
	enum JsonType {
		ANY,
		BOOLEAN,
		NUMBER,
		STRING,
		ARRAY,
		OBJECT
	};

	static GDExtensionAPIType number(bool p_optional = false) { return GDExtensionAPIType(JsonType::NUMBER, p_optional); }
	static GDExtensionAPIType string(bool p_optional = false) { return GDExtensionAPIType(JsonType::STRING, p_optional); }

	GDExtensionAPIType(JsonType p_type, bool p_optional);
	virtual ~GDExtensionAPIType();

	GDExtensionAPIType& set_array_subtype(const GDExtensionAPIType& p_type);
	GDExtensionAPIType& add_object_member(const String& p_name, const GDExtensionAPIType& p_type);

	String generate_definition() const;

private:
	union {
		Vector<Pair<String, GDExtensionAPIType>> object_member_types;
		GDExtensionAPIType array_type;
	} subtype;

	JsonType type;
	bool optional;
};

#endif

#endif // EXTENSION_API_DUMP_H
