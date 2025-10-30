import { useState } from "react";

export default function Dashboard() {
  const [activeTab, setActiveTab] = useState("agendamentos");

  const agendamentos = [
    { id: 1, cliente: "José Guilherme", barbeiro: "Francisco", servico: "Cabelo", data: "27/10/2025", horario: "10:00", status: "agendado" },
    { id: 2, cliente: "José Guilherme", barbeiro: "Francisco", servico: "Cabelo", data: "27/10/2025", horario: "10:00", status: "agendado" },
    { id: 3, cliente: "José Guilherme", barbeiro: "Francisco", servico: "Cabelo", data: "27/10/2025", horario: "10:00", status: "concluído" },
  ];

  return (
    <div className="min-h-screen bg-white text-gray-900">
      {/* Header */}
      <header className="flex items-center justify-between p-6 border-b">
        <div className="flex items-center gap-3">
          <div className="text-red-600 text-3xl font-bold">Cin</div>
          <div>
            <h1 className="text-xl font-semibold">Sistema de Gerenciamento - CinBarber</h1>
            <p className="text-sm text-gray-500">Painel do gerente</p>
          </div>
        </div>
      </header>

      {/* Nav */}
      <nav className="flex justify-center gap-4 bg-gray-200 py-3 rounded-md mx-10 mt-6">
        {["agendamentos", "funcionarios", "clientes"].map((tab) => (
          <button
            key={tab}
            onClick={() => setActiveTab(tab)}
            className={`px-6 py-2 rounded-full font-medium transition ${
              activeTab === tab
                ? "bg-white shadow text-red-600"
                : "text-gray-600 hover:text-red-600"
            }`}
          >
            {tab.charAt(0).toUpperCase() + tab.slice(1)}
          </button>
        ))}
      </nav>

      {/* Conteúdo */}
      <main className="p-10">
        {activeTab === "agendamentos" && (
          <>
            <div className="flex justify-between items-center mb-6">
              <h2 className="text-xl font-semibold">Lista de Agendamentos</h2>
              <button className="bg-red-600 text-white px-4 py-2 rounded-md hover:bg-red-700">
                + Novo Agendamento
              </button>
            </div>

            {/* Tabela */}
            <div className="overflow-x-auto">
              <table className="w-full border-collapse">
                <thead className="bg-gray-100 text-gray-700">
                  <tr>
                    {["Cliente", "Barbeiro", "Serviço", "Data", "Horário", "Status", "Ações"].map(
                      (col) => (
                        <th key={col} className="border-b px-4 py-2 text-left">
                          {col}
                        </th>
                      )
                    )}
                  </tr>
                </thead>
                <tbody>
                  {agendamentos.map((a) => (
                    <tr key={a.id} className="border-b hover:bg-gray-50">
                      <td className="px-4 py-2">{a.cliente}</td>
                      <td className="px-4 py-2">{a.barbeiro}</td>
                      <td className="px-4 py-2">{a.servico}</td>
                      <td className="px-4 py-2">{a.data}</td>
                      <td className="px-4 py-2">{a.horario}</td>
                      <td className="px-4 py-2">
                        <span
                          className={`px-3 py-1 rounded-full text-white text-sm ${
                            a.status === "agendado"
                              ? "bg-blue-600"
                              : "bg-green-500"
                          }`}
                        >
                          {a.status}
                        </span>
                      </td>
                      <td className="px-4 py-2">
                        <button className="text-blue-600 hover:underline mr-3">
                          Editar
                        </button>
                        <button className="text-red-600 hover:underline">
                          Excluir
                        </button>
                      </td>
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>
          </>
        )}

        {activeTab === "funcionarios" && (
          <div className="text-center text-gray-500 mt-10">
            <p>Gerenciamento de Funcionários (em desenvolvimento)</p>
          </div>
        )}

        {activeTab === "clientes" && (
          <div className="text-center text-gray-500 mt-10">
            <p>Lista de Clientes (em desenvolvimento)</p>
          </div>
        )}
      </main>
    </div>
  );
}
