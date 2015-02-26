class CSort{
public:
	CSort(int index, int order);

	int index;
	int order;
};

CSort::CSort(int index, int order){
	this->index = index;
	this->order = order;
}
