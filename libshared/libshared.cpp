#include "libshared.hpp"
#define BUF_SIZE 256
using namespace std;

char mkey[] = "shmfile";
string path_val;
fstream in_file;


// int
// _create_and_write_shared_memory (char *mmap_key, const char *value, unsigned int size){
    
//     int shm_fd;
    
//     /*Create a shared memory object in kernel space. If shared memory already
//      * exists it will truncate it to zero bytes again*/
//     shm_fd = shm_open(mmap_key, O_CREAT | O_RDWR | O_TRUNC, 0660);
    
//     if (shm_fd < 0) {
//         printf("failure on shm_open on shm_fd, errcode = %d\n", errno);
//         return -1;
//     }

//     if (ftruncate(shm_fd, size) == -1) {
//         printf("Error on ftruncate to allocate size of shared memory region\n");
//         return -1;
//     }

//     /*Now map the shared memory in kernel space into process's Virtual address space*/
//     void *shm_reg = mmap(NULL, // let the kernel chose to return the base address of shm memory
//             size,              // sizeof the shared memory to map to virtual address space of the process
//             PROT_READ | PROT_WRITE, // shared memory is Read and Writable
//             MAP_SHARED,        // shared memory is accessible by different processes
//             shm_fd,            // file descriptor of the shared memory 
//             0);                // offset from the base address of the physical/shared memory to be mapped

//     /* shm_reg is the address in process's Virtual address space, just like any other address.
//      * The Linux paging mechanism maps this address to starting address of the shared memory region 
//      * in kernel space. Any operation performed by process on shm_reg address is actually the operation
//      * performed in shared memory which resides in kernel*/
//     memset(shm_reg, 0, size);
//     memcpy(shm_reg, value, size);
//     munmap(shm_reg, size);
//     /*Reader process will not be able to read shm if writer unlink
//      * the name below*/
//     //shm_unlink(mmap_key);
//     close(shm_fd);
//     return size;
// }

// int
// _read_from_shared_memory (char *mmap_key, 
//                          char *buffer, 
//                          //unsigned int buff_size, 
//                          unsigned int bytes_to_read) {


//     int shm_fd = 0, rc = 0;

//     shm_fd = shm_open(mmap_key, O_CREAT | O_RDONLY , 0660);
    
//     if (shm_fd < 0) {
//         printf("failure on shm_open on shm_fd, error code = %d", errno);
//         return -1;
//     }

//     void *shm_reg = mmap (NULL, bytes_to_read, PROT_READ, MAP_SHARED, shm_fd, 0);

//     if(shm_reg == MAP_FAILED){
//         printf("Error on mapping\n");
//         return -1;
//     }
    
//     memcpy(buffer, shm_reg, bytes_to_read);
//     rc = munmap(shm_reg, bytes_to_read);

//     if(rc < 0){
//         printf("munmap failed\n");
//         return -1;
//     }
//     cout << "buffer from reading shm: " << buffer << endl;
//     close(shm_fd);
//     //return bytes_to_read; /*Return the number of bytes read */
//     return strlen(buffer);
// }


// unsigned short _get_buffer(char* buffer)
// {
//     int read_size = _read_from_shared_memory (mkey, buffer, BUF_SIZE);
//     cout << buffer << endl;
//     if(read_size == -1) return 255;
//     if(read_size == 0) return 4;
    
//     return 0;

// }

unsigned short load_resource(string path)
{
    //map<std::string, std::string> m;
    string buffer;
    string line;
    //string mk, mv;
    uint32_t buf_size;
    path_val = path;
    
    in_file.open(path, ios::out);
    if(!in_file.is_open()) 
    {
        perror("Resource file open error ..."); 
        return 1;
    }
    cout << "File " << path << " opened correctly" << endl;
    // while(getline(in_file, line))
    // {
    //     buffer.append(line + '\n');
    // }
    in_file.close();

    //buf_size = buffer.length();
    //char* buf_in_char = buffer.c_str();
    //char *buf_in_char = (char *)malloc(buf_size + 1);
    //memcpy(buf_in_char, buffer.c_str(), buf_size + 1);

    
    // int ret = _create_and_write_shared_memory (mkey, buffer.c_str(), buf_size + 1);
    // if(ret == -1)
    //     return 255;
    //cout << "Shared mem created with buffer: " << buffer << endl;
    return 0;
    

}

unsigned short get_value(const string& key, string& value)
{
     
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE);
    //int res = _get_buffer(buffer);
    string line {};
    if(!path_val.empty())
    {
        //int pos_key;
        //string buf_map(buffer);
        in_file.open(path_val, fstream::in);
        if(!in_file.is_open()) 
        {
            perror("Resource file open error ..."); 
            return 1;
        }
        while(getline(in_file, line))
        {
            if(line.find(key)!= string::npos)
            {
                value = line.substr(key.length() + 3, line.length() - key.length() - 3);
                in_file.close();
                return 0;
            }
                
        }
        in_file.close();
        // if((pos_key = buf_map.find(key)) != string::npos)
        // {
            
        //     int pos_break;
        //     if((pos_break = buf_map.find("\n", pos_key)) == string::npos) return 255;
        //     value = buf_map.substr(pos_key + key.length() + 3 , pos_break - (pos_key + key.length() + 3));
        //     return 0;
        // }
        // else
        return 3;

    }
    perror("No file available ...");
    return 255;

}

unsigned short set_value(const std::string& key, const std::string &value)
{
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE);
    //int res = _get_buffer(buffer);
    string line {};
    
    if(!path_val.empty())
    {
        in_file.open(path_val);
        cout << "File " << path_val << " opened correctly" << endl;
        if(!in_file.is_open()) 
        {
            perror("Resource file open error ..."); 
            return 1;
        }
        string text(
          (istreambuf_iterator<char>(in_file)),
          istreambuf_iterator<char>());
        in_file.close();
        size_t pos = 0;
        if ((pos = text.find(key, pos)) != string::npos) 
        {
                pos += key.length() + 3;
                int pos_break;
                if((pos_break = text.find("\n", pos)) == string::npos) return 255;
                //cout << "Pos is " << pos << " and pos break is " << pos_break;
                text.replace(pos , pos_break - pos, value);
                cout << text << endl;
                in_file.open(path_val, fstream::in | fstream::out | fstream::trunc);
                in_file << text; 
            
                in_file.close();
                return 0;
        }

        in_file.open(path_val, fstream::in | fstream::out | fstream::app);
	
        in_file << key << " : " << value << endl;
        // while(getline(in_file, line))
        // {
        //     if(line.find(key)!= string::npos)
        //     {
        //         //line.replace(key.length() + 3, line.length() - key.length() - 3, value);
        //         line.replace(0, line.length(), "");
        //         cout << "Value replaced " << endl;
        //         in_file.close();
        //         return 0;
        //     }
                
        // }

        in_file.close();
        // int pos_key;
        // string buf_map(buffer);
        // if((pos_key = buf_map.find(key)) != string::npos)
        // {
        //     int pos_break;
        //     if((pos_break = buf_map.find("\n", pos_key)) == string::npos) return 255;
        //     buf_map.replace(pos_key + key.length() + 3 , pos_break - (pos_key + key.length() + 3), value);
        // }
        // else
        // {
        //     buf_map.append(key + " : " + value + '\n') ;
        //     cout << buf_map << endl;
        // }
        // char *buf_in_char = new char[buf_map.length() + 1];
        // std::strcpy(buf_in_char, buf_map.c_str());
        // //mkey = ftok("shmfile",65); 
        // cout << "Set value: " << buf_in_char << endl;
        // int ret = _create_and_write_shared_memory (mkey, buf_in_char, buf_map.length() + 1);
        // if(ret == -1)
        //     return 255;
        

        // ofstream out_file;
        // out_file.open(path_val);
        // if(!out_file) return 255;
        // out_file << buf_in_char;
        // delete(buf_in_char);
        return 0;
       
    }
    perror("No file available ...");
    return 255;
}