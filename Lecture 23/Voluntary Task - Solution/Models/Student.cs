﻿using System;
using System.Collections.Generic;

namespace Voluntary_Task___Solution.Models;

public partial class Student
{
    public int Id { get; set; }

    public string Studentname { get; set; } = null!;

    public int Studentage { get; set; }

    public virtual ICollection<Grade> Grades { get; set; } = new List<Grade>();
}