package main

import (
    "fmt"
)

// 判断是否为闰年
func isLeapYear(year int) bool {
    return (year%4 == 0 && year%100!= 0) || (year%400 == 0)
}

// 获取某年某月的天数
func getDaysInMonth(year, month int) int {
    daysInMonth := [12]int{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    if month == 2 && isLeapYear(year) {
        return 29
    }
    return daysInMonth[month - 1]
}

// 获取某年1月1日是星期几
func getFirstDayOfYear(year int) int {
    return (1 + 5*((year - 1)%4) + 4*((year - 1)%100) + 6*((year - 1)%400)) % 7
}

// 打印日历头部
func printCalendarHeader(year, month int) {
    months := []string{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}
    fmt.Printf("\n%s %d\n", months[month - 1], year)
    fmt.Println("Sun Mon Tue Wed Thu Fri Sat")
}

// 打印某月的日历
func printMonthCalendar(year, month int) {
    printCalendarHeader(year, month)
    firstDay := getFirstDayOfYear(year)
    if month > 1 {
        for i := 0; i < month - 1; i++ {
            firstDay += getDaysInMonth(year, i + 1)
        }
        firstDay %= 7
    }
    for i := 0; i < firstDay; i++ {
        fmt.Printf("    ")
    }
    daysInMonth := getDaysInMonth(year, month)
    for day := 1; day <= daysInMonth; day++ {
        fmt.Printf("%3d ", day)
        if (firstDay + day)%7 == 0 {
            fmt.Println()
        }
    }
    if (firstDay + daysInMonth)%7!= 0 {
        fmt.Println()
    }
}

// 打印整年日历
func printYearCalendar(year int) {
    for month := 1; month <= 12; month++ {
        printMonthCalendar(year, month)
    }
}

func main() {
    var year int
    fmt.Print("Enter a year: ")
    fmt.Scan(&year)
    printYearCalendar(year)
}
