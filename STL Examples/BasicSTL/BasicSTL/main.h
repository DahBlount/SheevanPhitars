//STL Example Header
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <deque>
#include <string>		//This should (but it doesn't have to) be included if you want use the std namespace.
using namespace std;	//This is bad practice however.

//Create a basic struct we want to use in our map
struct mapSTRUCT
{
	int id;						//You don't actually need to make an id or key variable within the struct, this is just to prove a point
	string name;				//The name of the entry
};

/*You can also typedef your struct
typedef struct mapSTRUCTtype
{
	int id;						//You don't actually need to make an id or key variable within the struct, this is just to prove a point
	string name;				//The name of the entry
};
*/
//A map is a dynamic container of structs, where you have the name of a stuct object, and the key to the object. A map is an assocative container.
extern map<int, mapSTRUCT> testMap;			//The key to the object must be an integer, while the value inserted with the key is a struct, mySTRUCT to be exact.


//It's also possible to make your own versions of a map, but this isn't exactly the most straight forward job. It's also not required after MSVS 2005.

#if defined(_MSC_VER) && _MSC_VER >= 1400 || !defined(_MSC_VER)

#define DESTROY( type, p ) (p)->~type( )

template< typename T >
class my_allocator
{
public:
	typedef size_t		size_type;
	typedef T*			pointer;
	typedef const T*	const_pointer;
	typedef T			value_type;
	typedef ptrdiff_t	difference_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	/* portej05 does not like this particular function. */
	void construct(pointer p, const T& value)
	{
		::new (p)T(value);
	}

	void destroy(pointer p)
	{
		DESTROY(T, p);
	}

	pointer allocate(size_type n)
	{
		if (n == 0)
			return NULL;
		return (pointer)vm_malloc(n * sizeof(T));
	}

	template<class Other>
	pointer allocate(size_type n, const Other* hint = NULL)
	{
		(hint);
		return allocate(n);
	}

	void deallocate(pointer p, size_type)
	{
		if (p)
			vm_free(p);
	}

	template< class U >
	struct rebind
	{
		typedef my_allocator< U > other;
	};

	size_type max_size() const
	{	// Estimate process used by MS STL
		size_type _Count = (size_type)(-1) / sizeof(T);
		return (0 < _Count ? _Count : 1);
	}

	template< class T2 >
	my_allocator< T >& operator=(const my_allocator<T2>&)
	{
		return (*this);
	}

	my_allocator()
	{
	}

	my_allocator(const my_allocator< T >&)
	{
	}

	template< class T2 >
	my_allocator(const my_allocator< T2 >&)
	{
	}
};

template< typename T, typename U >
class My_map : public std::map<T, U, std::less<T>, SCP_vm_allocator<std::pair<const T, U> > > { };

#else

#define My_map std::map
#define My_vector std::vector
#define My_list std::list
#define My_queue std::queue
#define My_deque std::deque

#endif
//These are the basics of a map, but there are other STL types as well

struct stlSTRUCT
{
	int id;
	string name;
};

//A list is a similar to an array, but is limited to reading via forward or backward iteration from a known position. A sequence container.
extern list<stlSTRUCT> myList;			//In a list, the name would be used instead of the id as the key because the key to search for is also the name of the object you're looking for.

//A vector is a dynamically allocated array, meaning it can change in size before, during, or after runtime. A sequence container.
extern vector<stlSTRUCT> myVector;		//Similar to a list, the name of the struct object is also the key.

//A queue is like a list, but reads via a First-in, First-out context. Values are added to the back of the queue and pulled from the front of the queue. This is technically a container adaptor.
extern queue<string> myQueue;					//Queues are fairly straight forward(backward?), any type can be read in and out, just remember how you add and remove values.

//A deque is a double-ended queue, you can add and remove from both ends. It operates in a manner similar to a vector, but unlike a vector, not all of the elements are stored in a contiguous location.
extern deque<string> myDeque;					//Oddly enough, this isn't a container adaptor even though it's named after a queue! Instead this is classified as a sequence container.

/*
There are many more STL templates than what is shown here. You will see the following only rarely, and most likely not in game development.

#include <set>	(std::set, this is an associative container, only, unlike a map, its key is also its value)
#include <stack> (std::stack, this is a container adaptor, only you cannot iterate through this like a queue. It is built on top of a deque and follows a Last-in, first-out scheme, the element at the top of the stack is the one that was most recently added)
 
 There are also several derived template headers that are not officially part of STL, but those are even more rarely used. Ignore them for now.
*/

class INI_Reader
{
public:
	INI_Reader(class INI_Reader const &);
	INI_Reader(void);
	~INI_Reader(void);
	class INI_Reader & operator=(class INI_Reader const &);
	void close(void);
	bool find_header(char const *);
	bool get_bool(unsigned int);
	char const * get_file_name(void)const;
	char const * get_header_ptr(void);
	char const * get_indexed_value(unsigned int);
	int get_line_num(void)const;
	char const * get_line_ptr(void);
	char const * get_name(void)const;
	char const * get_name_ptr(void);
	unsigned int get_num_parameters(void)const;
	void get_state(struct State &)const;
	bool get_value_bool(unsigned int);
	float get_value_float(unsigned int);
	int get_value_int(unsigned int);
	char const * get_value_ptr(void);
	char const * get_value_string(unsigned int);
	char const * get_value_string(void);
	unsigned short const * get_value_wstring(void);
	class Vector  get_vector(void);
	bool is_end(void)const;
	bool is_header(char const *);
	bool is_number(char const *)const;
	bool is_value(char const *);
	bool is_value_empty(unsigned int);
	void log_link(char const *)const;
	bool open(char const *, bool);
	bool open_memory(char const *, unsigned int);
	bool read_header(void);
	bool read_value(void);
	void reset(void);
	void seek(unsigned int);
	void set_state(struct State const &);
	unsigned int tell(void)const;
	double value_num(unsigned int);

public:
	unsigned char data[5480];
};