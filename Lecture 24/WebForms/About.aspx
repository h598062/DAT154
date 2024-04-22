<%@ Page Title="About" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="About.aspx.cs" Inherits="WebForms.About" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">




    <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False">
        <Columns>
            <asp:BoundField DataField="studentname" HeaderText="Name" />
            <asp:BoundField DataField="studentage" HeaderText="Age" />
        </Columns>
    </asp:GridView>

    <hr />

    <asp:GridView ID="GridView2" runat="server" AutoGenerateColumns="True">
    </asp:GridView>





</asp:Content>
