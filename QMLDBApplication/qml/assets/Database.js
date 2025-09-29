.import QtQuick.LocalStorage 2.0 as Sql

function dbGetHandle()
{
    try {
        var db = Sql.LocalStorage.openDatabaseSync("NotesDB", "", "User notes", 1000000)
    } catch (err) {
        console.log("Error opening database: " + err)
    }
    return db
}

function dbInit()
{
    var db = Sql.LocalStorage.openDatabaseSync("NotesDB", "", "User notes", 1000000)
    try {
        db.transaction(function (tx) {
            tx.executeSql('CREATE TABLE IF NOT EXISTS Records (date text, note text)')
        })
    } catch (err) {
        console.log("Error creating table in database: " + err)
    }
}

function dbDelete(rowid)
{
    var db = dbGetHandle()
    db.transaction(function (tx) {
        tx.executeSql("DELETE FROM Records WHERE rowid = ?;", [rowid]);
    })
}

function dbUpdate(rowid, date, note)
{
    var db = dbGetHandle()
    db.transaction(function (tx) {
        tx.executeSql("UPDATE Records SET date = ?, note = ? WHERE rowid = ?;",
        [date, note, rowid]);
    })
}

function dbInsert(date, note)
{
    var db = dbGetHandle()
    var rowid = 0;
    db.transaction(function (tx) {
        tx.executeSql('INSERT INTO Records VALUES(?, ?)', [date, note])
        var result = tx.executeSql('SELECT last_insert_rowid()')
        rowid = result.insertId
    })
    return rowid
}

function dbReadAll()
{
    var db = dbGetHandle()
    db.transaction(function (tx) {
        var results = tx.executeSql('SELECT rowid, date, note FROM Records order by rowid desc')
        for (var i = 0; i < results.rows.length; i++) {
            noteModel.append({
                 rowid: results.rows.item(i).rowid,
                 date:  results.rows.item(i).date,
                 note:  results.rows.item(i).note
             })
        }
    })
}
