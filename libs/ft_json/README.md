# The humble JSON parser.

A C implementation of the JSON data-interchange format made as a school project (_school 42_)

## Building

This project requires **make** to be compiled, once installed simply type `make` in your shell to build the library.  

To build your program against the library link it using the compiler flags below:  
`-L $JSON_LIB_PATH 
-l ftjson -L$ LIBFT_PATH -l ft`  
where JSON_LIB_PATH and LIBFT_PATH corresponds to the folder where the json and libft libraries are located, respectively.

## Usage

**NOTE: To use the library, you must include `<json.h>`.  
The functions from `<json_internal.h>` should NEVER be used outside of the library !**

There are two ways to parse a JSON file using this library:
1. With `json_from_file()`:  
 Takes a file descriptor. (the return value of `open()`)

2. With`json_from_str()`:  
 Takes a string.
 
Both functions takes flags as their second argument, valid flags are:
* JFLAG_IGNORE_EXTRA: tells the parser to ignore characters after the end of the main object.
* JFLAG_ALLOW_COMMENTS: ignores comments. (`//` and `/**/`)
 
The return value of these function is pointer to an instance of `t_json_parse_res`.
Its `obj` member is set to `NULL` if a error occurred, in this case the `err` member string will contain the error message.  
Once done with it, it must be freed using `json_release_file()`.

#### Example:
```
t_json_parse_res *res = json_from_str("{\"is_computer_on\": true} hello there!", JSON_IGNORE_EXTRA | JSON_ALLOW_COMMENTS);

if (!res)
    exit(-1);
else if (!res->obj)
    puts(res->err ? res->err : "CRITICAL FAILURE, ABORT MISSION !!");
else
    do_something(res->obj);

json_release_file(&res, 1);
```

#### Using the JSON object:

The `t_json_value` type hides an union, thus to access its contents you must check the its type.  
All members of this union are structures that have a `t_json_vtype` named `type` as their first member,
so you can for example query the type like this: `some_value->obj.type` or `some_value->bol.type`.  

Each entry of `t_json_vtype` corresponds to a structure within `t_json_value`, expect for `JSON_NULL`.

**NOTE: the JSON_SPECIAL_CHAR is internal and MUST NOT be used !**

#### The other functions:
The [`<json.h>` header](https://github.com/MisterPeModder44/ft_json/blob/master/includes/json.h) contains all the function you might want to use and documentation about them.

## LICENSE:
The ft_json library is is licensed under the *GNU General Public License v3.0*
