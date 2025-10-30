export default function Funcionarios() {
  const funcionarios = [
    { nome: "João Silva", email: "joao@barbearia.com", contato: "11 99999-9999", funcao: "Barbeiro", expediente: "08h às 17h", salario: "R$ 2.500" },
    { nome: "Carlos Lima", email: "carlos@barbearia.com", contato: "11 98888-8888", funcao: "Atendente", expediente: "09h às 18h", salario: "R$ 1.800" },
  ];

  return (
    <div className="bg-white rounded-2xl shadow-md p-6">
      <div className="flex justify-between items-center mb-6">
        <h2 className="text-xl font-semibold text-gray-800">Funcionários</h2>
        <button className="bg-blue-500 hover:bg-blue-600 text-white font-medium px-4 py-2 rounded-lg">
          + Novo Funcionário
        </button>
      </div>

      <table className="w-full border-collapse">
        <thead>
          <tr className="bg-gray-200 text-gray-700">
            <th className="p-3 text-left">Nome</th>
            <th className="p-3 text-left">Email</th>
            <th className="p-3 text-left">Contato</th>
            <th className="p-3 text-left">Função</th>
            <th className="p-3 text-left">Expediente</th>
            <th className="p-3 text-left">Salário</th>
            <th className="p-3 text-center">Ações</th>
          </tr>
        </thead>
        <tbody>
          {funcionarios.map((f, i) => (
            <tr key={i} className="border-b hover:bg-gray-50">
              <td className="p-3">{f.nome}</td>
              <td className="p-3">{f.email}</td>
              <td className="p-3">{f.contato}</td>
              <td className="p-3">{f.funcao}</td>
              <td className="p-3">{f.expediente}</td>
              <td className="p-3">{f.salario}</td>
              <td className="p-3 text-center space-x-2">
                <button className="bg-yellow-400 hover:bg-yellow-500 text-white px-3 py-1 rounded-md">Editar</button>
                <button className="bg-red-500 hover:bg-red-600 text-white px-3 py-1 rounded-md">Excluir</button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}
