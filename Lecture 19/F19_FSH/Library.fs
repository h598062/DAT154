namespace F19_FSH

module Rain =
    open System
    let days = [1..365]

    type DayInfo (date:string, mm:float, ms:int) =
        member this.date = date
        member this.mm = mm
        member this.ms = ms

    let r = new System.Random()
    let intensity day =   
        match (day) with
        | d when d % 3 = 0 -> 50
        | d when d % 3 = 1 -> 40
        | d when d % 3 = 2 -> 0
        | _ -> 40

    let mm(day) = r.Next(0, intensity (day)) + r.Next(0, intensity (day))
    let ms(day) = r.Next(0,10)+r.Next(0,10)+r.Next(0,10)

    let dateOnly day = DateTime(2024, 1, 1).AddDays(day) |> DateOnly.FromDateTime
    let dayslist = days |> List.map(fun day -> DayInfo(dateOnly(day ).ToString(), mm(day), ms(day) ) ) 
    let raindays = dayslist  |> List.filter(fun (di) -> di.mm > 75 || di.ms > 20) |> List.sortBy(fun (di) -> di.date)


 


  
