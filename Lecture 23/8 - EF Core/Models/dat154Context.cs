﻿using Microsoft.EntityFrameworkCore;

namespace EFCore.Models {
    public partial class dat154Context : DbContext
    {
        public dat154Context()
        {
        }

        public dat154Context(DbContextOptions<dat154Context> options)
            : base(options)
        {
        }

        public virtual DbSet<Course> Courses { get; set; } = null!;

        public virtual DbSet<Grade> Grades { get; set; } = null!;

        public virtual DbSet<Student> Students { get; set; } = null!;

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (!optionsBuilder.IsConfigured)
            {
                optionsBuilder.UseSqlServer("data source=dat154.hvl.no,1443;initial catalog=dat154;user id=dat154;password=dat154;Encrypt=False");
            }
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.UseCollation("Danish_Norwegian_CI_AS");

            modelBuilder.Entity<Course>(entity =>
            {
                entity.HasKey(e => e.Coursecode)
                    .HasName("pk_course");

                entity.ToTable("course");

                entity.Property(e => e.Coursecode)
                    .HasMaxLength(6)
                    .IsUnicode(false)
                    .HasColumnName("coursecode")
                    .IsFixedLength();

                entity.Property(e => e.Coursename)
                    .HasMaxLength(50)
                    .IsUnicode(false)
                    .HasColumnName("coursename");

                entity.Property(e => e.Semester)
                    .HasMaxLength(1)
                    .IsUnicode(false)
                    .HasColumnName("semester")
                    .IsFixedLength();

                entity.Property(e => e.Teacher)
                    .HasMaxLength(50)
                    .IsUnicode(false)
                    .HasColumnName("teacher");
            });

            modelBuilder.Entity<Grade>(entity =>
            {
                entity.HasKey(e => new { e.Coursecode, e.Studentid })
                    .HasName("pk_grade");

                entity.ToTable("grade");

                entity.Property(e => e.Coursecode)
                    .HasMaxLength(6)
                    .IsUnicode(false)
                    .HasColumnName("coursecode")
                    .IsFixedLength();

                entity.Property(e => e.Studentid).HasColumnName("studentid");

                entity.Property(e => e.Grade1)
                    .HasMaxLength(1)
                    .IsUnicode(false)
                    .HasColumnName("grade")
                    .IsFixedLength();

                entity.HasOne(d => d.CoursecodeNavigation)
                    .WithMany(p => p.Grades)
                    .HasForeignKey(d => d.Coursecode)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("fk_course");

                entity.HasOne(d => d.Student)
                    .WithMany(p => p.Grades)
                    .HasForeignKey(d => d.Studentid)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("fk_student");
            });


            modelBuilder.Entity<Student>(entity =>
            {
                entity.ToTable("student");

                entity.Property(e => e.Id)
                    .ValueGeneratedNever()
                    .HasColumnName("id");

                entity.Property(e => e.Studentage).HasColumnName("studentage");

                entity.Property(e => e.Studentname)
                    .HasMaxLength(50)
                    .IsUnicode(false)
                    .HasColumnName("studentname");
            });



            OnModelCreatingPartial(modelBuilder);
        }

        partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
    }
}