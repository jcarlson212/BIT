#include <vector>
#include <iostream>

typedef long long int int64;

using namespace std;

class BIT {
    private:
        vector<int64> tree;

        int64 get_lowest_bit(int64 num){
            return num & (~(num-1));
        }

    public:
        //the size must be less than 2^(64)
        BIT(int64 size){
            this->tree = vector<int64>(size,0);
        }

        //updates value at index by increasing it by delta
        void update(int64 index, int64 delta){
            //10001000 -> 10010000 -> 10100000 -> ... 1000000
            //00001001 -> 00001010 -> 00001100 -> 00001000 ... -> 10000000
            while(index < this->tree.size()){
                tree[index] += delta;
                if(index == 0){
                    index++;
                }else{
                    int64 lowest_bit = get_lowest_bit(index);
                    index += lowest_bit;
                }
            }
        }

        //computes the prefix sum 0...i
        int64 prefix_sum(int64 index){
            int64 sum = 0;
            while(index > 0){
                sum += tree[index];
                if(index == 0){
                    break;
                }
                index -= get_lowest_bit(index);
            }
            return sum;
        } 

        //computes the sum left_index...right_index
        int64 range_sum(int64 left_index, int64 right_index){
            if(left_index > right_index){
                return 0;
            }
            return prefix_sum(right_index) - prefix_sum(left_index-1);
        }
};

int main(){
    ios::sync_with_stdio(0); 
    cin.tie(0); 
    cout << "running\n";
    BIT test(50);
    cout << "Output: \n"; 
    cout << test.range_sum(1, 49) << "\n";
    test.update(1, 100);
    cout << test.range_sum(1,1) << " " << test.range_sum(2,40) << "\n";
    test.update(5, 40);
    cout << test.range_sum(1, 4) << " " <<  test.range_sum(1, 6) << " " << test.range_sum(5,49) << " " << test.range_sum(1, 49) << "\n";
    
    return 0;
}