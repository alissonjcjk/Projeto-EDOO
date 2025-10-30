
export default function Agendamentos() {
  const agendamentos = [
    { cliente: "Lucas Silva", servico: "Corte de cabelo", data: "29/10/2025", horario: "14:00", barbeiro: "João Silva" },
    { cliente: "Mariana Souza", servico: "Barba", data: "29/10/2025", horario: "15:30", barbeiro: "Carlos Lima" },
  ];

  return (
    <div className="bg-white rounded-2xl shadow-md p-6">
      <div className="flex justify-between items-center mb-6">
        <h2 className="text-xl font-semibold text-gray-800">Agendamentos</h2>
        <button className="bg-blue-500 hover:bg-blue-600 text-white font-medium px-4 py-2 rounded-lg">
          + Novo Agendamento
        </button>
      </div>

      <table className="w-full border-collapse">
        <thead>
          <tr className="bg-gray-200 text-gray-700">
            <th className="p-3 text-left">Cliente</th>
            <th className="p-3 text-left">Serviço</th>
            <th className="p-3 text-left">Data</th>
            <th className="p-3 text-left">Horário</th>
            <th className="p-3 text-left">Barbeiro</th>
            <th className="p-3 text-center">Ações</th>
          </tr>
        </thead>
        <tbody>
          {agendamentos.map((a, i) => (
            <tr key={i} className="border-b hover:bg-gray-50">
              <td className="p-3">{a.cliente}</td>
              <td className="p-3">{a.servico}</td>
              <td className="p-3">{a.data}</td>
              <td className="p-3">{a.horario}</td>
              <td className="p-3">{a.barbeiro}</td>
              <td className="p-3 text-center space-x-2">
                <button className="bg-yellow-400 hover:bg-yellow-500 text-white px-3 py-1 rounded-md">Editar</button>
                <button className="bg-red-500 hover:bg-red-600 text-white px-3 py-1 rounded-md">Cancelar</button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}
