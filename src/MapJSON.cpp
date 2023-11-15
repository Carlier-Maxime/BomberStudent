
#include "MapJSON.h"
#include <string.h>
#include <stdio.h>
MapJSON::MapJSON(int idValue, int widthValue, int heightValue, char* contentValue){
	id=idValue;
	width = widthValue;
	height=heightValue;
	content=contentValue;
}

char* MapJSON::toJSON(){
	int length_height = 1;
	int tmp=height;
	while(tmp>9){
		tmp=tmp/10;
		length_height+=1;
	}
	int length_width = 1;
	tmp=width;
	while(tmp>9){
		tmp=tmp/10;
		length_width+=1;
	}
	int length_id = 1;
	tmp=id;
	while(tmp>9){
		tmp=tmp/10;
		length_id+=1;
	}
	int length_content = strlen(content);
	int totalLength=strlen(MAP_JSON_STRING_PROTOTYPE)+length_id+length_width+length_height+length_content;
	char* json = new char[totalLength];
	sprintf(json,MAP_JSON_STRING_PROTOTYPE,id,width,height,content);
	return json;

}