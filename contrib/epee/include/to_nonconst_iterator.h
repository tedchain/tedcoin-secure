#ifndef _TO_NONCONST_ITERATOR_H_
#define _TO_NONCONST_ITERATOR_H_

namespace epee
{

template<class Type>
typename Type::iterator to_nonsonst_iterator(Type& obj, typename Type::const_iterator it)
{
	typename Type::difference_type dist =  std::distance(static_cast<typename Type::const_iterator>(obj.begin()), it);
	typename Type::iterator res_it = obj.begin()+dist;
	return res_it;
}


template<class Type>
typename Type::iterator to_nonsonst_iterator(typename Type::iterator base_it, typename Type::const_iterator it)
{
	typename Type::difference_type dist =  std::distance(static_cast<typename Type::const_iterator>(base_it), it);
	typename Type::iterator res_it = base_it+dist;
	return res_it;
}
}//namespace epee
#endif //_TO_NONCONST_ITERATOR_H_
