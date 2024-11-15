#include <iostream>
#include <vector>
#include <chrono>

struct Trade {
    double price;
    int volume;
    long long time; // Время в наносекундах с начала эпохи
    int direction;
};

class Instrument {
public:
    std::vector<Trade> trades() const {
        // Возвращаем список сделок (предположим, что он уже заполнен)
        return trades_list;
    }

    void addTrade(const Trade& trade) {
        trades_list.push_back(trade);
    }

private:
    std::vector<Trade> trades_list;
};

class TradeVolumeCalculator {
public:
    static int calculateVolumeLast10Seconds(const Instrument& instrument) {
        auto now = std::chrono::system_clock::now().time_since_epoch().count();
        long long ten_seconds_in_nanos = 10 * 1000000000LL;
        long long start_time = now - ten_seconds_in_nanos;

        int total_volume = 0;
        for (const Trade& trade : instrument.trades()) {
            if (trade.time >= start_time) {
                total_volume += trade.volume;
            }
        }
        return total_volume;
    }
};

int main() {
    Instrument instrument;
    // Добавляем примерные сделки
    instrument.addTrade({100.0, 10, std::chrono::system_clock::now().time_since_epoch().count(), 1});
    instrument.addTrade({101.0, 5, std::chrono::system_clock::now().time_since_epoch().count(), -1});
    instrument.addTrade({102.0, 15,  std::chrono::system_clock::now().time_since_epoch().count(), -1});

    // Рассчитываем общий объем сделок за последние 10 секунд
    int total_volume = TradeVolumeCalculator::calculateVolumeLast10Seconds(instrument);
    std::cout << "Total volume in last 10 seconds: " << total_volume << std::endl;

    return 0;
}
