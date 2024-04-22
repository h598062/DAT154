using System;
using System.Collections.Generic;
using System.ComponentModel;

namespace WPFDemo.Models;

// This class is a bit more complicated than it needs to be
// for an Entity Framework model, but it has been modified
// to support property change notifications that lets the
// GUI be auto-updated. This also demonstrates that
// changing these classes is just fine.


public partial class Student : INotifyPropertyChanged
{
    public int Id { get; set; }

    private string _studentname = null!;
    public string Studentname { 
        get => _studentname; 
        set { 
            _studentname = value;
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Studentname)));
        }
    }

    private int _studentage = 0;
    public int Studentage {
        get => _studentage;
        set {
            _studentage = value;
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Studentage)));
        }
    }

    public virtual ICollection<Grade> Grades { get; set; } = [];

    public event PropertyChangedEventHandler? PropertyChanged;
}
