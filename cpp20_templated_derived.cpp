//Confusing error message when a templated derived class calls an function from a templated base class
//https://developercommunity.visualstudio.com/t/confusing-error-message-when-a-templated-derived-c/1048624

template<typename T>
class base
{
public:
	void myfun()
	{
	}
};

template<typename T>
class derived : public base<T>
{
public:
	using base<T>::myfun;
	//the following is one way of fixing
	//this
	//using base<T>::myfun;

	void call_base()
	{
		//the following call is one way of
		//fixing this
		//base<T>::myfun();
		myfun();
	}
};
