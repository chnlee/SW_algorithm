#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
struct Stock{
    int MNumber, MQuantity, MPrice;
};
// 연산자 오버로딩을 통해서 정렬 수행
struct Buy_Sort{
    bool operator()(Stock &a, Stock &b){
        if(a.MPrice == b.MPrice) return a.MNumber > b.MNumber;
        return a.MPrice < b.MPrice;
  }
};
struct Sell_Sort{
    bool operator()(Stock &a, Stock &b){
        if(a.MPrice == b.MPrice) return a.MNumber > b.MNumber;
        return a.MPrice > b.MPrice;
  }
};

// Stock을 이용하여 큐 생성
queue<Stock> temp;
// BestProfit을 위한 vector 배열 생성
vector<int> Profit[6];
// Buy, Sell 정렬을 우선 순위로 사용하여 우선순위 큐를 이용한다.
priority_queue<Stock,vector<Stock>,Buy_Sort> buy_list[6];
priority_queue<Stock,vector<Stock>,Sell_Sort> sell_list[6];
void init()
{ // 초기화 함수(temp, Profit, buy_list,sell_list 모두 초기화)
    while(! temp.empty()) temp.pop();
    for(int i=1; i<=5; ++i){
        while(! buy_list[i].empty()) buy_list[i].pop();
        while(! sell_list[i].empty()) sell_list[i].pop();
        Profit[i].clear();
  }
}

int buy(int mNumber, int mStock, int mQuantity, int mPrice)
{ // 만약 sell_list에 매도 하려는 주식이 없다면, 매수 정보 입력 및 Quantity 반환
    if(sell_list[mStock].empty()){
        buy_list[mStock].push({mNumber, mQuantity,mPrice}); 
        return mQuantity;
    }
  // 매도 주식 정보 생성(이미 정렬이 수행되었으므로 가장 우선순위에 있는 정보 입력받기)
    int Number = sell_list[mStock].top().MNumber;
    int Quantity = sell_list[mStock].top().MQuantity;
    int Price = sell_list[mStock].top().MPrice;
  // 매도 주식 정보 제거
    sell_list[mStock].pop();
  // 매수 가격, 매도 가격 비교
  // 매수 가격이 매도 가격보다 크거나 같은 경우
    if(mPrice >= Price){
    // 매수량, 매도량 비교
    // 1. 매수량이 매도량보다 많은 경우
        if(mQuantity>Quantity){
      //BestProfit을 위한 Price 삽입
            Profit[mStock].push_back(Price);
      // 새롭게 buy 함수 호출(new 매수량 = 기존 매수량 - 매도량)
            return buy(mNumber, mStock, mQuantity-Quantity, mPrice);
   }
    // 2. 매수량이 매도량보다 적은 경우
        else if(mQuantity < Quantity)
      // sell_list에 매도정보 삽입(new 매도량 = 기존 매도량 - 매수량)
            sell_list[mStock].push({Number,Quantity-mQuantity, Price}), mQuantity =0; 
    // 3. 매수량과 매도량이 같은 경우
        else mQuantity = 0;
        Profit[mStock].push_back(Price);
  }
  // 매수 가격이 매도 가격보다 작은 경우
    else{
    // buy_list와 sell_list에 기존 정보 삽입
        buy_list[mStock].push({mNumber,mQuantity,mPrice});
        sell_list[mStock].push({Number,Quantity,Price});
  }
    return mQuantity;
}

int sell(int mNumber, int mStock, int mQuantity, int mPrice)
{
  // 만약 buy_list에 매수 하려는 주식이 없다면, 매도 정보 입력 및 Quantity 반환
    if(buy_list[mStock].empty()){
        sell_list[mStock].push({mNumber, mQuantity,mPrice}); 
        return mQuantity;}
  // 매수 주식 정보 생성(이미 정렬이 수행되었으므로 가장 우선순위에 있는 정보 입력받기)
    int Number = buy_list[mStock].top().MNumber;
    int Quantity = buy_list[mStock].top().MQuantity;
    int Price = buy_list[mStock].top().MPrice;
  // 매수 주식 정보 제거
    buy_list[mStock].pop();
  // 매수 가격, 매도 가격 비교
  // 매도 가격이 매수 가격보다 크거나 같은 경우
    if(mPrice >= Price){
    // 매수량, 매도량 비교
    // 1. 매도량이 매수량보다 많은 경우
        if(mQuantity>Quantity){
      //BestProfit을 위한 Price 삽입
            Profit[mStock].push_back(Price);
      // 새롭게 buy 함수 호출(new 매도량 = 기존 매도량 - 매수량)
            return sell(mNumber, mStock, mQuantity-Quantity, mPrice);
   }
    // 2. 매도량이 매수량보다 적은 경우
        else if(mQuantity < Quantity){ 
      // buy_list에 매도정보 삽입(new 매수량 = 기존 매수량 - 매도량)
            buy_list[mStock].push({Number,Quantity-mQuantity, Price});mQuantity =0; 
    }
    // 3. 매수량과 매도량이 같은 경우
        else mQuantity = 0;
        Profit[mStock].push_back(Price);
  }
  // 매도 가격이 매수 가격보다 작은 경우
    else{
    // buy_list와 sell_list에 기존 정보 삽입
        buy_list[mStock].push({mNumber,mQuantity,mPrice});
        sell_list[mStock].push({Number,Quantity,Price});
  }
    return mQuantity;
}

void cancel(int mNumber)
{ 
    bool run = false;
  // mStock의 범위 만큼 반복수행
    for(int i=1; i<=5; i++){
    // buy_list가 비어있을 경우 continue
        if(buy_list[i].empty()) continue;
    // buy_list를 하나씩 삭제 후, 삭제한 정보를 temp에 삽입
        while(! buy_list[i].empty()){
            int Number = buy_list[i].top().MNumber;
            int Quantity = buy_list[i].top().MQuantity;
            int Price = buy_list[i].top().MPrice;
            buy_list[i].pop();
      // 만약 번호가 같은 경우 true
            if(Number==mNumber){
                run = true;
                break;
      }
            temp.push({Number,Quantity,Price});
    }
    // temp의 정보를 하나씩 꺼낸 후 모두 buy_list에 다시 삽입
        while(! temp.empty()){
            int Number = temp.front().MNumber;
            int Quantity = temp.front().MQuantity;
            int Price = temp.front().MPrice;
            temp.pop();
            buy_list[i].push({Number,Quantity,Price});
    }
        if(run) return ;
    }
    
  // sell_list 또한 마찬가지로 수행한다.
    for(int i=1; i<=5; i++){
        if(sell_list[i].empty()) continue;
        while(! sell_list[i].empty()){
            int Number = sell_list[i].top().MNumber;
            int Quantity = sell_list[i].top().MQuantity;
            int Price = sell_list[i].top().MPrice;
            sell_list[i].pop();
            if(Number==mNumber){
                run = true;
                break;
      }
            temp.push({Number,Quantity,Price});
    }
        while(! temp.empty()){
            int Number = temp.front().MNumber;
            int Quantity = temp.front().MQuantity;
            int Price = temp.front().MPrice;
            temp.pop();
            sell_list[i].push({Number,Quantity,Price});
   }
        if(run) return ; 
  }
}

int bestProfit(int mStock)
{ 
    int answer = 0;
  // Profit의 총 길이 구하기
    int temp = Profit[mStock].size();
  // i는 Profit의 가장 끝 index의 값을 의미함
    int i = Profit[mStock][temp-1];
  // 가장 끝 index-1부터 순차적으로 비교
    for(int j = temp-2; j>=0; --j){
        int k = Profit[mStock][j];
        answer = max(answer, i-k);
    // k가 i보다 큰 경우, i를 k값으로 갱신
        if(k>i){
            i = k;
        }
    }
    return answer;
}