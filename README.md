# lang-get

<br>
<br>
<br>

# Language.hxx

lang::get and lang::set are threadsafe and protected by a mutex.

<br>

## Language class
A wrapper around a dictionary(std::unordered_map) containing a find and insert function
Not meant to be used by the user in most cases.

<br>

## lang::get(...)
Looks up a the text correspoding to a given std::string key.
Returns the key if no entry in language matches the key.

### Parameters
1) key as const std::string &

### Return Value
The functions returns as string of the found text or a copy of the key.

<br>

## lang::set(...)
Sets the current lang of the program

### Parameters
1) std::shared_ptr to lang::Language

<br>
<br>
<br>

# load.hxx
load.hxx contains the loading function for languages in the namespace lang::load::

<br>

## lang::load::language(...)
### Parameters

1) langcode as string_view  
e.g. "en", "de", "fr" or "it"  

2) directory as std::filesystem::path  
It's the base directory containing all language folders.

3) files as std::span of std::filesystem::path  
These files are searched in the language folder.

### Return Value 
std::unique_ptr to lang::Language


# Directories
```
<assets/lang>  
+--en
|  +--foo.lang
|  +--bar.lang
|
+--de
|  +--foo.lang
|  +--bar.lang
|
+--it
|  +--foo.lang
|  +--bar.lang
|
+--fr
|  +--foo.lang
|  +--bar.lang
```

langcode = "en", "de", "fr" or "it"  
directory = "assets/lang"  
files = {"for.lang", bar.lang}  


# .lang Files
.lang files do have a really simple syntax. They only consist of a key/text pair per line


## Examples

```
"key1" : "text1"
"key2" : "text2"
```
