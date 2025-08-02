#include "Order.h"

Order::Order(): currentItemPage(0) {
    setupButtons();
}

int Order::show() {
    drawPage();
}

void Order::drawPage() {
    int y = 0;

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextDatum(TL_DATUM);
    M5.Lcd.setTextSize(2);
    M5.Lcd.drawString("新規注文",5, y);

    y +=35;

    M5.Lcd.drawLine(0, y, M5.Lcd.width(),y);

    y +=15;

    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextDatum(ML_DATUM);
    int startIndex = currentItemPage * 6;
    int endIndex = std::min(startIndex + 6, static_cast<int>(items.size()));
    for (int i = startIndex; i < endIndex; i++) {
        const auto& item = items[i];
        M5.Lcd.drawString(item.equipmentName, 10, y);
        M5.Lcd.drawString("¥" + String(item.price), 200, y);
        y += 30;
    }

    // スクロールボタンの描画
    scrollUpButton.draw();
    scrollDownButton.draw();
}

void Order::setupButtons() {
    scrollUpButton = MyButton(
        "▲",
        280, 40, 30, 30,
        [this]() { scrollUp(); },
        WHITE, BLACK, 1.4
    );

    scrollDownButton = MyButton(
        "▼",
        280, 180, 30, 30,
        [this]() { scrollDown(); },
        GREEN, WHITE, 1.4
    );
}

void Order::scrollUp() {
    if (currentItemPage > 0) {
        currentItemPage--;
        drawPage();
    }
}

void Order::scrollDown() {
    if ((currentItemPage + 1) * 6 < items.size()) {
        currentItemPage++;
        drawPage();
    }
}