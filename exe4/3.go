package main

import (
    "fmt"
    "time"
)

// 判断是否为闰年
func isLeapYear(year int) bool {
    return (year%4 == 0 && year%100!= 0) || year%400 == 0
}

// 获取每个月的天数
func daysInMonth(year, month int) int {
    days := []int{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    if month == 2 && isLeapYear(year) {
        return 29
    }
    return days[month - 1]
}

// 计算从1900年1月1日到指定日期的总天数
func totalDays(year, month, day int) int {
    total := 0
    for y := 1900; y < year; y++ {
        if isLeapYear(y) {
            total += 366
        } else {
            total += 365
        }
    }
    for m := 1; m < month; m++ {
        total += daysInMonth(year, m)
    }
    return total + day
}

// 打印日历
func printCalendar(year, month int) {
    fmt.Printf("      %d年%d月\n", year, month)
    fmt.Println(" 日 一 二 三 四 五 六")
    days := daysInMonth(year, month)
    firstDay := time.Date(year, time.Month(month), 1, 0, 0, 0, 0, time.UTC).Weekday()
    for i := 0; i < int(firstDay); i++ {
        fmt.Print("   ")
    }
    for d := 1; d <= days; d++ {
        fmt.Printf("%3d", d)
        if (int(firstDay)+d - 1)%7 == 6 {
            fmt.Println()
        }
    }
    if (int(firstDay)+days - 1)%7!= 6 {
        fmt.Println()
    }
}

func main() {
    now := time.Now()
    year := now.Year()
    month := int(now.Month())
    printCalendar(year, month)
}
