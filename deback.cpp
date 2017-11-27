#include <cstdio>
#include <string>
#include <cstdlib>

typedef struct{
std::string name;
std::string elem;
}Data;
int size=0;
Data* data = (Data*)std::malloc(0);

void setMsg(std::string name, std::string elem)
{
  int i=0,count=1;
  for(i=0;i<size;i++){
    if(data[i].name == name){
      data[i].elem = elem;
      count=2;
      break;
    }
  }

if(count == 1){
  size++;
  data = (Data*)std::realloc(data, size * sizeof(Data));
//  data[size] = (Data*)std::malloc(sizeof(Data));
//  size++;
  data[i].elem=elem;
  }
}

void deleteData(){
  int i;
//for (i=0;i<size;i++) {
  /* code */
std::free(data);
//}
}

std::string getElem(std::string name){
for (i = 0; i < size; i++) {
if(name == data[i].elem){
  data[i].name = name;
  return data[i].name;
  }  /* code */
}


  return "":
}

int main(int argc, char const *argv[]) {

  setMsg("a","b");
  printf("%s\n",data[0].elem.c_str());  /* code */
  return 0;
}
